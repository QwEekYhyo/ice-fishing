#include <SDL3/SDL_stdinc.h>

#include <common_defs.h>
#include <fish/fish.h>

// TODO: maybe use a macro for fish size (50) instead of hardcoding it everywhere

void move_fish(Fish* fish, unsigned long delta_time) {
    fish->x += delta_time * fish->speed;
    if (fish->speed > 0) {
        if (fish->x >= WINDOW_WIDTH) fish->state = DEAD;
    } else {
        if (fish->x <= -50) fish->state = DEAD;
    }
}

void spawn_fish(Fish* fish) {
    const float speed = (SDL_randf() * 2.0) - 1.0;
    if (speed == 0) return; // TODO: maybe something better?

    fish->state = ALIVE;
    fish->x     = speed > 0 ? -50 : WINDOW_WIDTH + 50;
    fish->y     = SDL_rand(WINDOW_HEIGHT - WATER_Y - 70) + WATER_Y + 10;
    fish->speed = speed;
}
