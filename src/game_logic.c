#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_stdinc.h>

#include <common_defs.h>
#include <fish/fish.h>
#include <game_logic.h>
#include <obstacle/obstacle.h>

void init_game(GameContext* ctx) {
    ctx->player_score = ctx->is_line_cut = ctx->caught_fish = 0;

    for (unsigned int i = 0; i < MAX_FISHES; i++) {
        ctx->fishes[i]        = SDL_malloc(sizeof(Fish));
        ctx->fishes[i]->state = DEAD;
    }

    for (unsigned int i = 0; i < MAX_OBSTACLES; i++) {
        ctx->obstacles[i]        = SDL_malloc(sizeof(Obstacle));
        ctx->obstacles[i]->alive = 0;
    }
}

bool handle_mouse_click(GameContext* ctx) {
    Fish* fish           = ctx->caught_fish;
    bool score_increased = 0;

    if (fish) {
        if (fish->y < WATER_Y) {
            fish->state = DEAD;
            ctx->player_score += 1;
            score_increased = 1;
        } else fish->state = RELEASED;

        ctx->caught_fish = 0;
    }

    if (ctx->is_line_cut) {
        float mouse_y;
        SDL_GetMouseState(NULL, &mouse_y);
        if (mouse_y < WATER_Y) {
            ctx->is_line_cut = 0;
        }
    }

    return score_increased;
}
