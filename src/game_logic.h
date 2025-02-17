#ifndef ICE_FISHING_GAME_LOGIC_H
#define ICE_FISHING_GAME_LOGIC_H

#include <fish/fish.h>

typedef enum {
    EMPTY,
    USED, // = there is a fish
    CUT,
} LineState;

typedef struct {
    Fish fishes[MAX_FISHES];
    unsigned long last_update;
    LineState line_state;
} GameContext;

void init_game(GameContext* ctx);

#endif
