#ifndef ICE_FISHING_OBSTACLE_H
#define ICE_FISHING_OBSTACLE_H

#include <SDL3/SDL_stdinc.h>

#define MAX_OBSTACLES 2
#define OBSTACLE_SIZE 75.0

typedef struct Obstacle {
    float x, y;
    float speed;
    Uint32 color;
    bool alive;
    void (*move)(struct Obstacle* self, unsigned long delta_time);
    void (*perform_action)(void* context);
} Obstacle;

void move_obstacle(Obstacle* obstacle, unsigned long delta_time);
void spawn_obstacle(Obstacle** obstacle);

#endif
