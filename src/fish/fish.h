#ifndef ICE_FISHING_FISH_H
#define ICE_FISHING_FISH_H

#define MAX_FISHES 4

typedef enum {
    DEAD,
    ALIVE,
    CAUGHT,
    RELEASED,
} FishState;

typedef struct {
    float x, y;
    float speed;
    FishState state;
} Fish;

void move_fish(Fish* fish, unsigned long delta_time);
void spawn_fish(Fish* fish);

#endif
