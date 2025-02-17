#include <drawing_utils.h>

void draw_rect_around_x(SDL_Renderer* renderer, SDL_FRect* rect) {
    const float half = rect->w / 2.0;
    rect->x -= half;
    SDL_RenderFillRect(renderer, rect);
    rect->x += half;
}

void draw_player(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 245, 0, 21, SDL_ALPHA_OPAQUE);
    SDL_FRect rect;
    rect.w = 100;
    rect.h = 150;
    rect.x = PLAYER_X;
    rect.y = WATER_Y - 170.0; // 170 is player height (150) + ice height (20)
    draw_rect_around_x(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    rect.w = 60;
    rect.h = 90;
    rect.y += 45.0;
    draw_rect_around_x(renderer, &rect);
}
