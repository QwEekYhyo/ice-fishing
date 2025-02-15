#include <stdlib.h>

#include "game_logic.h"

void move_fish(Fish* fish, unsigned long delta_time) { fish->x += delta_time * fish->speed; }

void init_game(GameContext* ctx) {
    for (int i = 0; i < MAX_FISHES; i++) {
        ctx->fishes[i]        = malloc(sizeof(Fish));
        ctx->fishes[i]->speed = 0.1 * i;
        ctx->fishes[i]->x     = 0;
        ctx->fishes[i]->y     = 70 * i + 50;
    }
}
