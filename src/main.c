#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_timer.h>

#include <SDL3_ttf/SDL_ttf.h>

#include <SDL3_image/SDL_image.h>

#include <common_defs.h>
#include <drawing_utils.h>
#include <fish/fish.h>
#include <game_logic.h>
#include <obstacle/obstacle.h>

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Surface* score_surface;
    SDL_Texture* score_texture;
    GameContext* ctx;
} AppState;

static SDL_Texture* test;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    SDL_SetAppMetadata("Ice Fishing", "0.1", "fr.puceaulytech.ice-fishing");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!TTF_Init()) {
        SDL_Log("Couldn't initialize SDL_ttf: %s", SDL_GetError());
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

    as->font = TTF_OpenFont("../assets/comicrazy.ttf", 100); // TODO: better path resolution
    if (!as->font) {
        SDL_Log("Couldn't open font: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    as->score_surface = NULL;
    as->score_texture = NULL;
    update_player_score(as->renderer, as->font, &as->score_surface, &as->score_texture, 0);

    as->ctx = SDL_malloc(sizeof(GameContext));
    init_game(as->ctx);

    SDL_Surface* test_surface =
        IMG_Load("../assets/fishingrod.png"); // TODO: better path resolution
    test = SDL_CreateTextureFromSurface(as->renderer, test_surface);
    SDL_DestroySurface(test_surface);

    load_fish_textures(as->renderer);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    if (event->type == SDL_EVENT_QUIT) return SDL_APP_SUCCESS;

    if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        AppState* as = (AppState*) appstate;
        if (handle_mouse_click(as->ctx))
            update_player_score(
                as->renderer,
                as->font,
                &as->score_surface,
                &as->score_texture,
                as->ctx->player_score
            );
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
    AppState* as     = (AppState*) appstate;
    GameContext* ctx = as->ctx;

    SDL_FRect rect;
    /* Draw background */
    draw_background(as->renderer, &rect);

    /* Draw player score */
    rect.x = 40;
    rect.y = 20;
    rect.w = 200;
    rect.h = 70;
    SDL_RenderTexture(as->renderer, as->score_texture, NULL, &rect);

    /* Draw static player */
    draw_player(as->renderer);
    rect.h = rect.w = 150;

    rect.x = HOOK_X;
    rect.y = WATER_Y - 200;
    SDL_RenderTexture(as->renderer, test, NULL, &rect);

    /* Draw fishing line and hook */
    float mouse_y;
    SDL_GetMouseState(NULL, &mouse_y);
    mouse_y = SDL_max(mouse_y, rect.y + 5);
    SDL_SetRenderDrawColor(as->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderLine(as->renderer, HOOK_X, rect.y, HOOK_X, mouse_y);

    if (!ctx->is_line_cut) {
        rect.w = rect.h = 24;
        rect.x = HOOK_X;
        rect.y = mouse_y;
        SDL_SetRenderDrawColor(as->renderer, 246, 250, 1, SDL_ALPHA_OPAQUE);
        draw_rect_around_x(as->renderer, &rect);
    }

    /* Draw fishes */
    draw_all_fishes(as->renderer, ctx, &rect);

    /* Draw obstacles */
    draw_all_obstacles(as->renderer, ctx, &rect);

    SDL_RenderPresent(as->renderer);
    ctx->last_update = SDL_GetTicks();

    SDL_Delay(20);
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    if (appstate == NULL) return;

    AppState* as = (AppState*) appstate;
    SDL_DestroySurface(as->score_surface);
    SDL_DestroyTexture(as->score_texture);
    SDL_DestroyTexture(test);
    SDL_DestroyRenderer(as->renderer);
    SDL_DestroyWindow(as->window);
    TTF_CloseFont(as->font);

    for (int i = 0; i < MAX_FISHES; i++)
        SDL_free(as->ctx->fishes[i]);

    for (int i = 0; i < MAX_OBSTACLES; i++)
        SDL_free(as->ctx->obstacles[i]);

    SDL_free(as->ctx);
    SDL_free(as);
    TTF_Quit();
    SDL_Quit();
}
