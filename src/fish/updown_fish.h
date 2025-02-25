#ifndef ICE_FISHING_UPDOWN_FISH_H
#define ICE_FISHING_UPDOWN_FISH_H

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>

#include <fish/fish.h>

typedef struct {
    Fish base;
    char current_direction;
    unsigned char no_direction_changes;
} UpDownFish;

void up_down_fish_load_texture(SDL_Renderer* renderer);
void up_down_fish_move(Fish* self, unsigned long delta_time);
void up_down_fish_new(Fish* self);

#endif
