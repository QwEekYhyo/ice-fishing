#ifndef ICE_FISHING_GAME_LOGIC_H
#define ICE_FISHING_GAME_LOGIC_H

#include <stdbool.h>

#include <fish/fish.h>

typedef struct {
    Fish fishes[MAX_FISHES];
    unsigned long last_update;
    bool is_line_cut;
    Fish* caught_fish;
} GameContext;

void init_game(GameContext* ctx);

#endif
