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

#define STB_DS_IMPLEMENTATION
#include <stb_ds.h>

#include <common_defs.h>
#include <drawing_utils.h>
#include <fish/fish.h>
#include <game_logic.h>
#include <obstacle/obstacle.h>
#include <text.h>

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    TextLabel* score_text;
    TextLabel* lives_text;
    GameContext* ctx;
} AppState;

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

    as->font = TTF_OpenFont("../assets/comicrazy.ttf", 40); // TODO: better path resolution
    if (!as->font) {
        SDL_Log("Couldn't open font: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    as->score_text =
        text_label_new(as->font, (SDL_Color) { 0, 0, 0, 255 }, get_player_score_text(0));

    as->ctx = SDL_malloc(sizeof(GameContext));
    init_game(as->ctx);

    as->lives_text =
        text_label_new(as->font, (SDL_Color) { 0, 0, 0, 255 }, get_player_lives_text(as->ctx->player_lives));

    init_textures(as->ctx, as->renderer);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    if (event->type == SDL_EVENT_QUIT) return SDL_APP_SUCCESS;

    if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        AppState* as = (AppState*) appstate;
        MouseClickResult result = handle_mouse_click(as->ctx);
        if (result & SCORE_UPDATED)
            text_label_set(as->score_text, get_player_score_text(as->ctx->player_score));
        if (result & LIVES_UPDATED)
            text_label_set(as->lives_text, get_player_lives_text(as->ctx->player_lives));
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
    AppState* as     = (AppState*) appstate;
    GameContext* ctx = as->ctx;

    SDL_FRect rect;
    /* Draw background */
    draw_background(as->renderer, &rect);

    /* Draw player lives */
    text_label_render(
        as->renderer,
        as->lives_text,
        10.0f,
        2.0f
    );

    /* Draw player score */
    text_label_render(
        as->renderer,
        as->score_text,
        HOOK_X - 20.0f - 2.0f * as->score_text->w,
        WATER_Y - ICE_HEIGHT - 10.0f - as->score_text->h
    );

    /* Draw static player & its fishing rod */
    draw_player(as->renderer);
    rect.h = rect.w = 150;

    rect.x = HOOK_X;
    rect.y = WATER_Y - 180.0f - ICE_HEIGHT;
    SDL_RenderTexture(as->renderer, shget(ctx->textures, "fishing_rod"), NULL, &rect);

    /* Draw fishing line and hook */
    float mouse_y;
    SDL_GetMouseState(NULL, &mouse_y);
    mouse_y = SDL_max(mouse_y, rect.y + 5);
    SDL_SetRenderDrawColor(as->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderLine(
            as->renderer,
            HOOK_X,
            rect.y,
            HOOK_X,
            ctx->is_line_cut ? mouse_y - 50.0f : mouse_y
    );

    if (!ctx->is_line_cut) {
        rect.w = rect.h = 24;
        rect.x          = HOOK_X;
        rect.y          = mouse_y;
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
    text_label_free(as->score_text);

    int nb_textures = shlen(as->ctx->textures);
    for (int i = 0; i < nb_textures; i++)
        SDL_DestroyTexture(as->ctx->textures[i].value);
    shfree(as->ctx->textures);

    SDL_DestroyRenderer(as->renderer);
    SDL_DestroyWindow(as->window);
    if (TTF_WasInit()) TTF_CloseFont(as->font);

    for (int i = 0; i < MAX_FISHES; i++)
        SDL_free(as->ctx->fishes[i]);

    for (int i = 0; i < MAX_OBSTACLES; i++)
        SDL_free(as->ctx->obstacles[i]);

    SDL_free(as->ctx);
    SDL_free(as);
    TTF_Quit();
    SDL_Quit();
}
