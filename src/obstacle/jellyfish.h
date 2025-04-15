#ifndef ICE_FISHING_JELLYFISH_H
#define ICE_FISHING_JELLYFISH_H

#include <obstacle/obstacle.h>

typedef struct {
    Obstacle base;
} Jellyfish;

void jellyfish_move(Obstacle* self, unsigned long delta_time);
bool jellyfish_action_check(Obstacle* self, const void* context, const SDL_FRect* hook_rect);
void jellyfish_action(void* context);
void jellyfish_new(Obstacle* self);

#endif
