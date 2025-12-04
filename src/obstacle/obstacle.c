#include <SDL3/SDL_stdinc.h>

#include <common_defs.h>
#include <obstacle/barrel.h>
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

Obstacle* spawn_obstacle(Obstacle* obstacle) {
    float speed = (SDL_randf() * 0.3f) + 0.1f;
    if (speed == 0.0f) speed = 0.3f;
    else if (SDL_randf() >= 0.5f) speed *= -1.0f;

    static const Uint8 OBSTACLE_TYPE_NUMBER = 2;
    const Uint8 random_obstacle_type        = SDL_rand(OBSTACLE_TYPE_NUMBER);

    // TODO: different probabilities for each type of obstacle
    size_t size;
    switch (random_obstacle_type) {
    default:
        return obstacle;
    case 0:
        size = sizeof(Barrel);
        break;
    case 1:
        size = sizeof(Jellyfish);
        break;
    }
    // Maybe it would be more efficient
    // to just alloc ONCE the size of the biggest obstacle
    obstacle = SDL_realloc(obstacle, size);

    obstacle->alive = 1;
    obstacle->y     = SDL_rand(WINDOW_HEIGHT - WATER_Y - 70) + WATER_Y + 10;
    obstacle->speed = speed;

    switch (random_obstacle_type) {
    case 0:
        barrel_new(obstacle);
        break;
    case 1:
        jellyfish_new(obstacle);
        break;
    }

    obstacle->x = speed >= 0 ? -obstacle->w : WINDOW_WIDTH + obstacle->w;

    return obstacle;
}
