#ifndef ICE_FISHING_TEXT_H
#define ICE_FISHING_TEXT_H

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3_ttf/SDL_ttf.h>

typedef struct {
    char* text_content;
    TTF_Font* font;
    SDL_Color color;
    float w, h;
    SDL_Texture* texture;
    bool dirty;
} TextLabel;

void text_label_set(TextLabel* text_label, const char* new_text);
void text_label_render(SDL_Renderer* renderer, TextLabel* text_label, float x, float y);
void text_label_free(TextLabel* text_label);
TextLabel* text_label_new(TTF_Font* font, SDL_Color color, const char* text);

/* Text buffer manipulation utils */
const char* get_player_score_text(Uint32 score);
const char* get_player_lives_text(Uint8 lives);

/* Temporary sortof mutex shit */
void release_text_buffer();

#endif
