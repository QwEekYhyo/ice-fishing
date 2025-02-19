#include <SDL3/SDL_stdinc.h>

#include <common_defs.h>
#include <fish/fish.h>

// TODO: maybe use a macro for fish size (50) instead of hardcoding it everywhere

void move_fish(Fish* fish, unsigned long delta_time) {
    fish->properties->_move(fish, delta_time);

    if (
        fish->speed > 0 && fish->x >= WINDOW_WIDTH ||
        fish->speed < 0 && fish->x <= -50
    )
        fish->state = DEAD;
}

void spawn_fish(Fish* fish, const FishProperties* properties) {
    const float speed = (SDL_randf() * 2.0) - 1.0;
    if (speed == 0) return; // TODO: maybe something better?

    fish->state = ALIVE;
    fish->x     = speed > 0 ? -50 : WINDOW_WIDTH + 50;
    fish->y     = SDL_rand(WINDOW_HEIGHT - WATER_Y - 70) + WATER_Y + 10;
    fish->speed = speed;
    fish->properties = properties;
}

void move_linear(Fish *fish, unsigned long delta_time) {
    fish->x += delta_time * fish->speed;
}

// This is kinda trash
void random_ups_downs(Fish* fish, unsigned long delta_time) {
    move_linear(fish, delta_time);
    bool can_go_up = fish->y >= WATER_Y + 20;
    bool can_go_down = fish->y <= WINDOW_HEIGHT - 20 - 50;

    if (!can_go_down && !can_go_up) return;

    float delta_y = (SDL_randf() - 1) * delta_time * fish->speed;
    if (can_go_down && can_go_up)
        fish->y += delta_y;
    else if (can_go_down)
        fish->y += SDL_fabsf(delta_y);
    else if (can_go_up)
        fish->y -= SDL_fabsf(delta_y);
}
