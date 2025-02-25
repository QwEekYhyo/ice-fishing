#include <SDL3_image/SDL_image.h>

#include <fish/normal_fish.h>

static SDL_Texture* texture = NULL;

void normal_fish_load_texture(SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load("../assets/fish.png"); // TODO: better path resolution
    texture              = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
}

void normal_fish_move(Fish* fish, unsigned long delta_time) {
    NormalFish* self = (NormalFish*) fish;
    self->base.x += delta_time * self->base.speed;
}

void normal_fish_new(Fish* fish) {
    NormalFish* self = (NormalFish*) fish;

    self->base.w       = 150.0f;
    self->base.h       = 50.0f;
    self->base.texture = texture;
    self->base.move    = normal_fish_move;
}
