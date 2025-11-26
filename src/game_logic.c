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

/**************** TEXTURE CODE ****************/
/*  I might move this to another file later   */
typedef struct {
    const char* name;
    const char* path;
} TextureEntry;

void init_textures(GameContext* ctx, SDL_Renderer* renderer) {
    ctx->textures = NULL;

    // TODO: better path resolution
    TextureEntry texture_entries[] = {
        { "normal_fish", "../assets/fish.png" },
        { "up_down_fish", "../assets/greyfish.png" },
        { "fishing_rod", "../assets/fishingrod.png" },
        { "barrel_obstacle", "../assets/barrel.png" },
        { "jellyfish_obstacle", "../assets/jellyfish.png" },
    };

    // TODO: default texture

    for (unsigned int i = 0; i < sizeof(texture_entries) / sizeof(texture_entries[0]); i++) {
        SDL_Surface* surface = IMG_Load(texture_entries[i].path);
        if (!surface) {
            SDL_Log("Failed to load %s: %s", texture_entries[i].path, SDL_GetError());
            continue;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        shput(ctx->textures, texture_entries[i].name, texture);
        SDL_DestroySurface(surface);
    }
}

/**************** END OF TEXTURE CODE ****************/

MouseClickResult handle_mouse_click(GameContext* ctx) {
    Fish* fish           = ctx->caught_fish;
    MouseClickResult res = 0;

    if (fish) {
        if (fish->y < WATER_Y) {
            fish->state = DEAD;
            ctx->player_score += 1;
            res |= SCORE_UPDATED;
        } else {
            fish->state = RELEASED;
        }

        ctx->caught_fish = 0;
    }

    if (ctx->is_line_cut && ctx->player_lives > 0) {
        float mouse_y;
        SDL_GetMouseState(NULL, &mouse_y);
        if (mouse_y < WATER_Y) {
            ctx->is_line_cut = 0;
            ctx->player_lives--;
            res |= LIVES_UPDATED;
        }
    }

    return res;
}
