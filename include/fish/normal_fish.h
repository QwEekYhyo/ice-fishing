#ifndef ICE_FISHING_NORMAL_FISH_H
#define ICE_FISHING_NORMAL_FISH_H

#include <SDL3/SDL_render.h>

#include <fish/fish.h>

typedef struct {
    Fish base;
} NormalFish;

void normal_fish_move(Fish* self, unsigned long delta_time);
void normal_fish_new(Fish* self);

#endif
