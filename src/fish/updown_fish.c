#include <SDL3_image/SDL_image.h>

#include <common_defs.h>
#include <fish/updown_fish.h>

static SDL_Texture* texture = NULL;

void up_down_fish_load_texture(SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load("../assets/poop.png"); // TODO: better path resolution
    texture              = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
}

void up_down_fish_move(Fish* fish, unsigned long delta_time) {
    UpDownFish* self = (UpDownFish*) fish;

    if (self->no_direction_changes <= 10) {
        self->base.x += delta_time * self->base.speed;

        bool can_go_up   = self->base.y >= WATER_Y + 20;
        bool can_go_down = self->base.y <= WINDOW_HEIGHT - 20 - 50;

        self->no_direction_changes++;
        if (can_go_down && self->current_direction == 1)
            self->base.y += delta_time * SDL_fabsf(self->base.speed) * 0.5;
        else if (can_go_up && self->current_direction == -1)
            self->base.y -= delta_time * SDL_fabsf(self->base.speed) * 0.5;
    } else {
        self->no_direction_changes = 0;
        self->current_direction    = SDL_rand(3) - 1;
        up_down_fish_move(fish, delta_time);
    }
}

void up_down_fish_new(Fish* fish) {
    UpDownFish* self = (UpDownFish*) fish;

    self->base.texture         = texture;
    self->base.move            = up_down_fish_move;
    self->no_direction_changes = 50;
}
