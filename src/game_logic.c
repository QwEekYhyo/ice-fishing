#include <fish/fish.h>
#include <game_logic.h>

void init_game(GameContext* ctx) {
    ctx->player_score = 
    ctx->is_line_cut = 
    ctx->caught_fish = 0;

    for (unsigned int i = 0; i < MAX_FISHES; i++) {
        ctx->fishes[i].state = DEAD;
    }
}
