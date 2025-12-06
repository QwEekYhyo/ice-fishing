#include <SDL3/SDL_log.h>
#include <SDL3/SDL_stdinc.h>

#include <common_defs.h>
#include <obstacle/barrel.h>
#include <obstacle/crab.h>
#include <obstacle/jellyfish.h>
#include <obstacle/obstacle.h>

typedef enum {
    CRAB_NONE  = 0,
    CRAB_LEFT  = 1 << 1,
    CRAB_RIGHT = 1 << 0,
} CrabPosition;

#define CRAB_FULL(crabs) ((crabs & CRAB_LEFT) && (crabs & CRAB_RIGHT))

static CrabPosition current_crabs = CRAB_NONE;

void move_obstacle(Obstacle* obstacle, unsigned long delta_time) {
    obstacle->move(obstacle, delta_time);

    if (
        (obstacle->speed > 0 && obstacle->x >= WINDOW_WIDTH) ||
        (obstacle->speed < 0 && obstacle->x <= -obstacle->w)
    ) {
        obstacle->alive = 0;
        if (obstacle->type == OBSTACLETYPE_CRAB) {
            // If speed is negative when 'dying'
            //   => crab is going from right to left
            //   => crab is on the left of the hole
            current_crabs &= ~(1 << (obstacle->speed < 0));
        }
    }
}

// TODO: different probabilities for each type of obstacle
typedef struct {
    size_t size;
    void (*init)(Obstacle*);
} ObstacleDesc;

static const ObstacleDesc OBSTACLE_DESCS[OBSTACLE_TYPE_NUMBER] = {
    [OBSTACLETYPE_BARREL]    = { sizeof(Barrel), barrel_new },
    [OBSTACLETYPE_JELLYFISH] = { sizeof(Jellyfish), jellyfish_new },
    [OBSTACLETYPE_CRAB]      = { sizeof(Crab), crab_new }, // MUST BE LAST
};

Obstacle* spawn_obstacle(Obstacle* obstacle) {
    float speed = (SDL_randf() * 0.3f) + 0.1f;

    // This is why crab must be last in the list
    const Uint8 new_type =
        SDL_rand(CRAB_FULL(current_crabs) ? OBSTACLE_TYPE_NUMBER - 1 : OBSTACLE_TYPE_NUMBER);
    const ObstacleDesc* obstacle_desc = &OBSTACLE_DESCS[new_type];

    // Maybe it would be more efficient
    // to just alloc ONCE the size of the biggest obstacle
    void* new_memory = SDL_realloc(obstacle, obstacle_desc->size);
    if (!new_memory) {
        SDL_Log("Failed to realloc obstacle");
        return obstacle;
    }
    obstacle = new_memory;

    obstacle->type  = new_type;
    obstacle->alive = 1;
    obstacle->y     = SDL_rand(WINDOW_HEIGHT - WATER_Y - 70) + WATER_Y + 10;

    if (new_type == OBSTACLETYPE_CRAB) {
        if (current_crabs & CRAB_LEFT) {
            speed = -speed;
            current_crabs |= CRAB_RIGHT;
        } else {
            current_crabs |= CRAB_LEFT;
        }
    } else if (SDL_randf() >= 0.5f) {
        speed = -speed;
    }

    obstacle->speed = speed;

    obstacle_desc->init(obstacle);

    obstacle->x = obstacle->speed >= 0 ? -obstacle->w : WINDOW_WIDTH + obstacle->w;

    return obstacle;
}
