#ifndef ICE_FISHING_DRAWING_UTILS_H
#define ICE_FISHING_DRAWING_UTILS_H

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>

#include <SDL3_ttf/SDL_ttf.h>

#include <common_defs.h>

void draw_rect_around_x(SDL_Renderer* renderer, SDL_FRect* rect);

void draw_player(SDL_Renderer* renderer);

void update_player_score(
        SDL_Renderer* renderer,
        TTF_Font* font,
        SDL_Surface** surface,
        SDL_Texture** texture,
        unsigned long score);

#endif
