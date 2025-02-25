#ifndef ICE_FISHING_FISH_H
#define ICE_FISHING_FISH_H

#include <SDL3/SDL_stdinc.h>

// Maybe I'll make this dynamic at some point
#define MAX_FISHES 4
#define FISH_SIZE 50.0

typedef enum {
    DEAD,
    ALIVE,
    CAUGHT,
    RELEASED,
} FishState;

typedef struct Fish {
    float x, y;
    float speed;
    Uint32 color;
    FishState state;
    void (*move)(struct Fish* self, unsigned long delta_time);
} Fish;

void move_fish(Fish* fish, unsigned long delta_time);
Fish* spawn_fish(Fish* fish);

#endif
