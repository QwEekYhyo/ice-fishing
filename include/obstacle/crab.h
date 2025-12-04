#ifndef ICE_FISHING_CRAB_H
#define ICE_FISHING_CRAB_H

#include <SDL3/SDL_stdinc.h>

#include <obstacle/obstacle.h>

enum CrabState {
    CRABSTATE_MOVING_FORWARD,
    CRABSTATE_PERFORMING_ACTION,
    CRABSTATE_PERFORMED_ACTION,
    CRABSTATE_MOVING_BACKWARD,
};

typedef struct {
    Obstacle base;
    Uint8 state;
    Uint64 start_time;
} Crab;

void crab_move(Obstacle* self, unsigned long delta_time);
bool crab_action_check(Obstacle* self, const void* context, const SDL_FRect* hook_rect);
void crab_action(void* context);
void crab_new(Obstacle* self);

#endif
