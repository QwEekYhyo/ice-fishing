#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#define MAX_FISHES 4

typedef struct {
    float x, y;
    float speed;
} Fish;

typedef struct {
    Fish* fishes[MAX_FISHES];
    unsigned long last_update;
} GameContext;

void move_fish(Fish* fish, unsigned long delta_time);

void init_game(GameContext* ctx);

#endif
