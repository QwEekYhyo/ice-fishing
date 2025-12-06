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
    /* Hash Map storing all textures */
    struct texture_lookup* textures;
    /* Array of all fishes */
    Fish* fishes[MAX_FISHES];
    /* Array of all obstacles */
    Obstacle* obstacles[MAX_OBSTACLES];
    /* Ticks of last game update */
    Uint64 last_update;
    /* Player's score AKA number of fishes caught */
    Uint32 player_score;
    /* Player's lives AKA number of hooks remaining */
    Uint8 player_lives;
    /* Is the player's line currently cut */
    bool is_line_cut;
    /* The fish currently on the line */
    Fish* caught_fish;
} GameContext;

void init_game(GameContext* ctx);
void init_textures(GameContext* ctx, SDL_Renderer* renderer);

typedef enum {
    SCORE_UPDATED = 1 << 0,
    LIVES_UPDATED = 1 << 1,
} MouseClickResult;

MouseClickResult handle_mouse_click(GameContext* context);

#endif
