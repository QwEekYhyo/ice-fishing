#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <fish/fish.h>

typedef struct {
    Fish* fishes[MAX_FISHES];
    unsigned long last_update;
} GameContext;

void init_game(GameContext* ctx);

#endif
