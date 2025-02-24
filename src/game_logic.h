#ifndef ICE_FISHING_GAME_LOGIC_H
#define ICE_FISHING_GAME_LOGIC_H

#include <stdbool.h>

#include <fish/fish.h>
#include <obstacle/obstacle.h>

typedef struct {
    Fish* fishes[MAX_FISHES];
    Obstacle* obstacles[MAX_OBSTACLES];
    unsigned long last_update;
    unsigned long player_score;
    bool is_line_cut;
    Fish* caught_fish;
} GameContext;

void init_game(GameContext* ctx);

/* Returns true if the player score needs to be updated */
bool handle_mouse_click(GameContext* context);

#endif
