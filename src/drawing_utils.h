#ifndef DRAWING_UTILS_H
#define DRAWING_UTILS_H

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

#include <common_defs.h>

void draw_rect_around_x(SDL_Renderer* renderer, SDL_FRect* rect);

void draw_player(SDL_Renderer* renderer);

#endif
