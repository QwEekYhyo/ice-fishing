#include <SDL3/SDL_atomic.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>

#include <text.h>

void text_label_set(TextLabel* text_label, const char* new_text) {
    if (SDL_strcmp(text_label->text_content, new_text) != 0) {
        SDL_free(text_label->text_content);
        text_label->text_content = SDL_strdup(new_text);
        release_text_buffer();
        text_label->dirty = true;
    }
}

void text_label_render(SDL_Renderer* renderer, TextLabel* text_label, float x, float y) {
    if (text_label->dirty) {
        if (text_label->texture) SDL_DestroyTexture(text_label->texture);

        SDL_Surface* surface = TTF_RenderText_Solid_Wrapped(
            text_label->font,
            text_label->text_content,
            SDL_strlen(text_label->text_content),
            text_label->color,
            0
        );
        text_label->texture = SDL_CreateTextureFromSurface(renderer, surface);
        text_label->w       = surface->w;
        text_label->h       = surface->h;
        SDL_DestroySurface(surface);
        text_label->dirty = false;
    }

    SDL_FRect dst = { x, y, text_label->w, text_label->h };
    SDL_RenderTexture(renderer, text_label->texture, NULL, &dst);
}

void text_label_free(TextLabel* text_label) {
    if (!text_label) return;

    SDL_DestroyTexture(text_label->texture);
    SDL_free(text_label->text_content);
    SDL_free(text_label);
}

TextLabel* text_label_new(TTF_Font* font, SDL_Color color, const char* text) {
    TextLabel* label = SDL_malloc(sizeof(TextLabel));

    label->font         = font;
    label->color        = color;
    label->text_content = SDL_strdup(text);
    release_text_buffer();
    label->texture = NULL;
    label->w       = 0.0f;
    label->h       = 0.0f;
    label->dirty   = true;

    return label;
}

#define TEXT_BUFFER_SIZE 100
static char text[TEXT_BUFFER_SIZE];
static SDL_AtomicInt used = { 0 };

/* If wondering, SDL_snprintf does add the null-terminator */

const char* get_player_score_text(Uint32 score) {
    if (SDL_GetAtomicInt(&used)) SDL_Log("Warning: re-using unreleased text buffer");

    SDL_snprintf(text, TEXT_BUFFER_SIZE, " %u\nFish", score);
    SDL_AtomicIncRef(&used);

    return text;
}

const char* get_player_lives_text(Uint8 lives) {
    if (SDL_GetAtomicInt(&used)) SDL_Log("Warning: re-using unreleased text buffer");

    SDL_snprintf(text, TEXT_BUFFER_SIZE, "x %u", lives);
    SDL_AtomicIncRef(&used);

    return text;
}

void release_text_buffer() {
    SDL_AtomicDecRef(&used);
}
