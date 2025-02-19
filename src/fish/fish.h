#ifndef ICE_FISHING_FISH_H
#define ICE_FISHING_FISH_H

#include <SDL3/SDL_stdinc.h>

// Maybe I'll make this dynamic at some point
#define MAX_FISHES 4

typedef enum {
    DEAD,
    ALIVE,
    CAUGHT,
    RELEASED,
} FishState;

struct Fish;

typedef struct {
    Uint32 color;
    void (*_move)(struct Fish* fish, unsigned long delta_time);
} FishProperties;

typedef struct Fish {
    float x, y;
    float speed;
    FishState state;
    const FishProperties* properties;
} Fish;

void move_fish(Fish* fish, unsigned long delta_time);
void spawn_fish(Fish* fish, const FishProperties* properties);

/* These functions are not to be used as is */
void move_linear(Fish* fish, unsigned long delta_time);
void random_ups_downs(Fish* fish, unsigned long delta_time);

#endif
