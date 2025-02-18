#include <common_defs.h>
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

void handle_mouse_click(GameContext* ctx) {
    Fish* fish = ctx->caught_fish;
    if (fish) {
        if (fish->y < WATER_Y) {
            fish->state = DEAD;
            ctx->player_score += 1;
        } else fish->state = RELEASED;
        
        ctx->caught_fish = 0;
    }
}
