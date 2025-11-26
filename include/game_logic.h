#ifndef ICE_FISHING_GAME_LOGIC_H
#define ICE_FISHING_GAME_LOGIC_H

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>

#include <fish/fish.h>
#include <obstacle/obstacle.h>

struct texture_lookup {
    const char* key;
    SDL_Texture* value;
};

typedef struct {
    struct texture_lookup* textures;
    Fish* fishes[MAX_FISHES];
    Obstacle* obstacles[MAX_OBSTACLES];
    Uint64 last_update;
    Uint32 player_score;
    Uint8 player_lives;
    bool is_line_cut;
    Fish* caught_fish;
} GameContext;

void init_game(GameContext* ctx);
void init_textures(GameContext* ctx, SDL_Renderer* renderer);

/* Returns true if the player score needs to be updated */
bool handle_mouse_click(GameContext* context);

#endif
