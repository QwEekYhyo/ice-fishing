#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>

#include <stb_ds.h>

#include <drawing_utils.h>
#include <fish/fish.h>
#include <obstacle/obstacle.h>

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

static const SDL_Color color = { 0, 0, 0, 255 };
static char text[100];

void update_player_score(
    SDL_Renderer* renderer,
    TTF_Font* font,
    SDL_Surface** surface,
    SDL_Texture** texture,
    unsigned long score
) {
    SDL_snprintf(text, 100, " %lu\nFish", score);

    if (*surface) SDL_DestroySurface(*surface);
    if (*texture) SDL_DestroyTexture(*texture);

    *surface = TTF_RenderText_Solid_Wrapped(font, text, SDL_strlen(text), color, 0);
    *texture = SDL_CreateTextureFromSurface(renderer, *surface);
}

void draw_all_fishes(SDL_Renderer* renderer, GameContext* ctx, const SDL_FRect* hook_rect) {
    Uint64 now   = SDL_GetTicks();
    Uint64 delta = now - ctx->last_update;

    SDL_FRect fish_rect;
    for (int i = 0; i < MAX_FISHES; i++) {
        Fish* current_fish = ctx->fishes[i];
        if (current_fish->state == DEAD) {
            Sint32 probability = SDL_rand(100);
            /* This might seem very low but it's not */
            if (probability < 1) ctx->fishes[i] = spawn_fish(current_fish);
        } else {
            fish_rect.w = current_fish->w;
            fish_rect.h = current_fish->h;
            if (current_fish->state == CAUGHT) {
                fish_rect.y = current_fish->y = hook_rect->y + 15;
                fish_rect.x = current_fish->x = HOOK_X;

                fish_rect.x -= fish_rect.w / 2.0;
                fish_rect.y += fish_rect.h / 2.0;
                SDL_RenderTextureRotated(
                    renderer,
                    shget(ctx->textures, current_fish->texture),
                    NULL,
                    &fish_rect,
                    -90.0l,
                    NULL,
                    SDL_FLIP_NONE
                );
            } else {
                move_fish(current_fish, delta);
                fish_rect.x = current_fish->x;
                fish_rect.y = current_fish->y;

                SDL_RenderTextureRotated(
                    renderer,
                    shget(ctx->textures, current_fish->texture),
                    NULL,
                    &fish_rect,
                    0.0l,
                    NULL,
                    current_fish->speed > 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL
                );

                if (
                        current_fish->state == ALIVE &&
                        !ctx->caught_fish &&
                        !ctx->is_line_cut &&
                        SDL_HasRectIntersectionFloat(hook_rect, &fish_rect)
                ) {
                    current_fish->state = CAUGHT;
                    ctx->caught_fish    = current_fish;
                }
            }
        }
    }
}

void draw_all_obstacles(SDL_Renderer* renderer, GameContext* ctx, const SDL_FRect* hook_rect) {
    Uint64 now   = SDL_GetTicks();
    Uint64 delta = now - ctx->last_update;

    SDL_FRect obstacle_rect;
    for (int i = 0; i < MAX_OBSTACLES; i++) {
        Obstacle* current_obstacle = ctx->obstacles[i];
        if (current_obstacle->alive == 0) {
            Sint32 probability = SDL_rand(150);
            if (probability < 1) ctx->obstacles[i] = spawn_obstacle(current_obstacle);
        } else {
            move_obstacle(current_obstacle, delta);

            obstacle_rect.x = current_obstacle->x;
            obstacle_rect.y = current_obstacle->y;
            obstacle_rect.w = current_obstacle->w;
            obstacle_rect.h = current_obstacle->h;

            SDL_RenderTextureRotated(
                renderer,
                shget(ctx->textures, current_obstacle->texture),
                NULL,
                &obstacle_rect,
                20.0l,
                NULL,
                current_obstacle->speed > 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL
            );

            if (current_obstacle->should_perform_action(current_obstacle, ctx, hook_rect))
                current_obstacle->perform_action(ctx);
        }
    }
}
