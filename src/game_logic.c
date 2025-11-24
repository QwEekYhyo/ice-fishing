#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_stdinc.h>

#include <SDL3_image/SDL_image.h>

#include <stb_ds.h>

#include <common_defs.h>
#include <fish/fish.h>
#include <game_logic.h>
#include <obstacle/obstacle.h>

void init_game(GameContext* ctx) {
    ctx->player_lives = 3;
    ctx->player_score = 0;
    ctx->is_line_cut  = 0;
    ctx->caught_fish  = 0;

    for (unsigned int i = 0; i < MAX_FISHES; i++) {
        ctx->fishes[i]        = SDL_malloc(sizeof(Fish));
        ctx->fishes[i]->state = DEAD;
    }

    for (unsigned int i = 0; i < MAX_OBSTACLES; i++) {
        ctx->obstacles[i]        = SDL_malloc(sizeof(Obstacle));
        ctx->obstacles[i]->alive = 0;
    }
}

void init_textures(GameContext* ctx, SDL_Renderer* renderer) {
    ctx->textures = NULL;

    SDL_Surface* surface;
    SDL_Texture* texture;

    // TODO: default texture

    surface = IMG_Load("../assets/fish.png"); // TODO: better path resolution
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    shput(ctx->textures, "normal_fish", texture);
    SDL_DestroySurface(surface);

    surface = IMG_Load("../assets/greyfish.png"); // TODO: better path resolution
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    shput(ctx->textures, "up_down_fish", texture);
    SDL_DestroySurface(surface);

    surface = IMG_Load("../assets/fishingrod.png"); // TODO: better path resolution
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    shput(ctx->textures, "fishing_rod", texture);
    SDL_DestroySurface(surface);
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

    if (ctx->is_line_cut && ctx->player_lives > 0) {
        float mouse_y;
        SDL_GetMouseState(NULL, &mouse_y);
        if (mouse_y < WATER_Y) {
            ctx->is_line_cut = 0;
            ctx->player_lives--;
        }
    }

    return score_increased;
}
