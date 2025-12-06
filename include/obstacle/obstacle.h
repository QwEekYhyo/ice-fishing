#ifndef ICE_FISHING_OBSTACLE_H
#define ICE_FISHING_OBSTACLE_H

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_stdinc.h>

#define MAX_OBSTACLES 2

#define OBSTACLE_TYPE_NUMBER 3
typedef enum {
    OBSTACLETYPE_BARREL    = 0,
    OBSTACLETYPE_JELLYFISH = 1,
    OBSTACLETYPE_CRAB      = 2,
} ObstacleType;

typedef struct Obstacle {
    ObstacleType type;
    float x, y, w, h; // Maybe directly store an SDL_FRect??
    float speed;
    const char* texture;
    double texture_angle;
    bool alive;
    void (*move)(struct Obstacle* self, unsigned long delta_time);
    bool (*should_perform_action)(
        struct Obstacle* self,
        const void* context,
        const SDL_FRect* hook_rect
    );
    void (*perform_action)(void* context);
} Obstacle;

void move_obstacle(Obstacle* obstacle, unsigned long delta_time);
Obstacle* spawn_obstacle(Obstacle* obstacle);

#endif
