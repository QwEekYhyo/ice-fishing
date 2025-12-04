#include <SDL3/SDL_log.h>
#include <SDL3/SDL_stdinc.h>

#include <common_defs.h>
#include <obstacle/barrel.h>
#include <obstacle/crab.h>
#include <obstacle/jellyfish.h>
#include <obstacle/obstacle.h>

void move_obstacle(Obstacle* obstacle, unsigned long delta_time) {
    obstacle->move(obstacle, delta_time);

    if (
        (obstacle->speed > 0 && obstacle->x >= WINDOW_WIDTH) ||
        (obstacle->speed < 0 && obstacle->x <= -obstacle->w)
    )
        obstacle->alive = 0;
}

#define OBSTACLE_TYPE_NUMBER 3
typedef enum {
    OBSTACLETYPE_BARREL = 0,
    OBSTACLETYPE_JELLYFISH = 1,
    OBSTACLETYPE_CRAB = 2,
} ObstacleType;

// TODO: different probabilities for each type of obstacle
typedef struct {
    size_t size;
    void (*init)(Obstacle*);
} ObstacleDesc;

static const ObstacleDesc OBSTACLE_DESCS[OBSTACLE_TYPE_NUMBER] = {
    [OBSTACLETYPE_BARREL]    = { sizeof(Barrel),    barrel_new },
    [OBSTACLETYPE_JELLYFISH] = { sizeof(Jellyfish), jellyfish_new },
    [OBSTACLETYPE_CRAB]      = { sizeof(Crab),      crab_new },
};

Obstacle* spawn_obstacle(Obstacle* obstacle) {
    float speed = (SDL_randf() * 0.3f) + 0.1f;
    if (SDL_randf() >= 0.5f) speed = -speed;

    const Uint8 random_type = SDL_rand(OBSTACLE_TYPE_NUMBER);
    const ObstacleDesc* obstacle_desc = &OBSTACLE_DESCS[random_type];

    // Maybe it would be more efficient
    // to just alloc ONCE the size of the biggest obstacle
    void* new_memory = SDL_realloc(obstacle, obstacle_desc->size);
    if (!new_memory) {
        SDL_Log("Failed to realloc obstacle");
        return obstacle;
    }
    obstacle = new_memory;

    obstacle->alive = 1;
    obstacle->y     = SDL_rand(WINDOW_HEIGHT - WATER_Y - 70) + WATER_Y + 10;
    obstacle->speed = speed;

    obstacle_desc->init(obstacle);

    obstacle->x = speed >= 0 ? -obstacle->w : WINDOW_WIDTH + obstacle->w;

    return obstacle;
}
