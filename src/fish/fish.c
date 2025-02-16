#include <SDL3/SDL_stdinc.h>

#include <common_defs.h>
#include <fish/fish.h>

void move_fish(Fish* fish, unsigned long delta_time) {
    fish->x += delta_time * fish->speed;
    if (fish->x >= WINDOW_WIDTH)
        fish->state = DEAD;
}

void spawn_fish(Fish* fish) {
    fish->state = ALIVE;
    fish->x = -50;
    fish->y = SDL_rand(WINDOW_HEIGHT - WATER_Y - 70) + WATER_Y + 10;
    fish->speed = (SDL_rand(70) + 1) / 100.0;
}
