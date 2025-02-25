#ifndef ICE_FISHING_FISH_H
#define ICE_FISHING_FISH_H

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>

// Maybe I'll make this dynamic at some point
#define MAX_FISHES 4
#define FISH_WIDTH 150.0f
#define FISH_HEIGHT 50.0f

typedef enum {
    DEAD,
    ALIVE,
    CAUGHT,
    RELEASED,
} FishState;

typedef struct Fish {
    float x, y;
    float speed;
    SDL_Texture* texture;
    FishState state;
    void (*move)(struct Fish* self, unsigned long delta_time);
} Fish;

void load_fish_textures(SDL_Renderer* renderer);

void move_fish(Fish* fish, unsigned long delta_time);
Fish* spawn_fish(Fish* fish);

#endif
