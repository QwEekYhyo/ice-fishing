#ifndef ICE_FISHING_BARREL_H
#define ICE_FISHING_BARREL_H

#include <obstacle/obstacle.h>

typedef struct {
    Obstacle base;
} Barrel;

void barrel_move(Obstacle* self, unsigned long delta_time);
bool barrel_action_check(Obstacle* self, const void* context, const SDL_FRect* hook_rect);
void barrel_action(void* context);
void barrel_new(Obstacle* self);

#endif
