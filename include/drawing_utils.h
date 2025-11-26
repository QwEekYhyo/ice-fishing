#ifndef ICE_FISHING_DRAWING_UTILS_H
#define ICE_FISHING_DRAWING_UTILS_H

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>

#include <SDL3_ttf/SDL_ttf.h>

#include <common_defs.h>
#include <game_logic.h>

void draw_rect_around_x(SDL_Renderer* renderer, SDL_FRect* rect);

void draw_background(SDL_Renderer* renderer, SDL_FRect* rect);
void draw_player(SDL_Renderer* renderer);

void draw_all_fishes(SDL_Renderer* renderer, GameContext* ctx, const SDL_FRect* hook_rect);
void draw_all_obstacles(SDL_Renderer* renderer, GameContext* ctx, const SDL_FRect* hook_rect);

#endif
