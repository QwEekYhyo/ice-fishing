#ifndef FISH_H
#define FISH_H

#define MAX_FISHES 4

typedef struct {
    float x, y;
    float speed;
} Fish;

void move_fish(Fish* fish, unsigned long delta_time);

#endif
