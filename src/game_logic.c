#include <fish/fish.h>
#include <game_logic.h>

void init_game(GameContext* ctx) {
    for (unsigned int i = 0; i < MAX_FISHES; i++) {
        ctx->fishes[i].state = DEAD;
    }
}
