#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>

#include <drawing_utils.h>

void draw_rect_around_x(SDL_Renderer* renderer, SDL_FRect* rect) {
    const float half = rect->w / 2.0;
    rect->x -= half;
    SDL_RenderFillRect(renderer, rect);
    rect->x += half;
}

void draw_background(SDL_Renderer* renderer, SDL_FRect* rect) {
    /* All the screen white */
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    /* Fill all screen but the sky with ice color */
    SDL_SetRenderDrawColor(renderer, 75, 132, 211, SDL_ALPHA_OPAQUE);
    rect->w = WINDOW_WIDTH;
    rect->h = WINDOW_HEIGHT;
    rect->x = 0;
    rect->y = WATER_Y - 20.0;
    SDL_RenderFillRect(renderer, rect);

    /* Then fill with water under the water line */
    SDL_SetRenderDrawColor(renderer, 31, 58, 94, SDL_ALPHA_OPAQUE);
    rect->y = WATER_Y;
    SDL_RenderFillRect(renderer, rect);

    /* Draw the hole in the ice */
    SDL_SetRenderDrawColor(renderer, 48, 89, 145, SDL_ALPHA_OPAQUE);
    rect->w = 100.0;
    rect->h = 20.0;
    rect->y = WATER_Y - 20.0;
    rect->x = HOOK_X;
    draw_rect_around_x(renderer, rect);
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

static const SDL_Color color = {0, 0, 0, 255};
static char text[100];

void update_player_score(
    SDL_Renderer* renderer,
    TTF_Font* font,
    SDL_Surface** surface,
    SDL_Texture** texture,
    unsigned long score
) {
    SDL_snprintf(text, 100, "%lu Fish", score);

    if (*surface) SDL_DestroySurface(*surface);
    if (*texture) SDL_DestroyTexture(*texture);

    *surface = TTF_RenderText_Solid(font, text, SDL_strlen(text), color);
    *texture = SDL_CreateTextureFromSurface(renderer, *surface);
}
