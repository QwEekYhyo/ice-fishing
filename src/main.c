#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>

#include <game_logic.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define WATER_Y WINDOW_HEIGHT / 3.0

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    GameContext* ctx;
} AppState;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    SDL_SetAppMetadata("Ice Fishing", "0.1", "fr.puceaulytech.ice-fishing");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    AppState* as = SDL_malloc(sizeof(AppState));
    if (!as) return SDL_APP_FAILURE;

    *appstate = as;

    if (!SDL_CreateWindowAndRenderer(
            "Ice Fishing",
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            0,
            &as->window,
            &as->renderer
        )) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    as->ctx = SDL_malloc(sizeof(GameContext));
    init_game(as->ctx);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    if (event->type == SDL_EVENT_QUIT) return SDL_APP_SUCCESS;

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
    AppState* as = (AppState*) appstate;

    /* Draw background */
    SDL_SetRenderDrawColor(as->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(as->renderer);

    SDL_FRect rect;
    SDL_SetRenderDrawColor(as->renderer, 75, 132, 211, SDL_ALPHA_OPAQUE);
    rect.w = WINDOW_WIDTH;
    rect.h = WINDOW_HEIGHT;
    rect.y = WATER_Y - 20.0;
    SDL_RenderFillRect(as->renderer, &rect);

    SDL_SetRenderDrawColor(as->renderer, 31, 58, 94, SDL_ALPHA_OPAQUE);
    rect.y = WATER_Y;
    SDL_RenderFillRect(as->renderer, &rect);

    Uint64 now           = SDL_GetTicks();
    Uint64 delta         = now - as->ctx->last_update;
    as->ctx->last_update = now;
    SDL_SetRenderDrawColor(as->renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);

    for (int i = 0; i < MAX_FISHES; i++) {
        Fish* current_fish = &as->ctx->fishes[i];
        move_fish(current_fish, delta);
        rect.x = current_fish->x;
        rect.y = current_fish->y + WATER_Y;
        rect.w = 50;
        rect.h = 50;
        SDL_RenderFillRect(as->renderer, &rect);
    }

    SDL_RenderPresent(as->renderer);

    SDL_Delay(100);
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    if (appstate == NULL) return;

    AppState* as = (AppState*) appstate;
    SDL_DestroyRenderer(as->renderer);
    SDL_DestroyWindow(as->window);
    SDL_free(as->ctx);
    SDL_free(as);
}
