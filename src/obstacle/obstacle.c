#include <SDL3/SDL_stdinc.h>

#include <common_defs.h>
#include <obstacle/obstacle.h>
#include <obstacle/barrel.h>
#include <obstacle/jellyfish.h>

void move_obstacle(Obstacle* obstacle, unsigned long delta_time) {
    obstacle->move(obstacle, delta_time);

    if (
        (obstacle->speed > 0 && obstacle->x >= WINDOW_WIDTH) ||
        (obstacle->speed < 0 && obstacle->x <= -OBSTACLE_SIZE)
    )
        obstacle->alive = 0;
}

Obstacle* spawn_obstacle(Obstacle* obstacle) {
    const float speed = (SDL_randf() * 0.3) + 0.1;
    if (speed == 0) return obstacle; // TODO: maybe something better?

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
    obstacle = SDL_realloc(obstacle, size);

    obstacle->alive = 1;
    obstacle->x     = speed > 0 ? -OBSTACLE_SIZE : WINDOW_WIDTH + OBSTACLE_SIZE;
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

    return obstacle;
}
