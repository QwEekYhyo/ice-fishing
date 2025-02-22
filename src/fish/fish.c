#include <SDL3/SDL_stdinc.h>

#include <common_defs.h>
#include <fish/fish.h>
#include <fish/normal_fish.h>
#include <fish/updown_fish.h>


void move_fish(Fish* fish, unsigned long delta_time) {
    fish->move(fish, delta_time);

    if (
        (fish->speed > 0 && fish->x >= WINDOW_WIDTH) ||
        (fish->speed < 0 && fish->x <= -FISH_SIZE)
    )
        fish->state = DEAD;
}

void spawn_fish(Fish** fish) {
    const float speed = (SDL_randf() * 2.0) - 1.0;
    if (speed == 0) return; // TODO: maybe something better?

    static const Uint8 FISH_TYPE_NUMBER = 2;
    const Uint8 random_fish_type        = SDL_rand(FISH_TYPE_NUMBER);

    // TODO: different probabilities for each type of fish
    size_t size;
    switch (random_fish_type) {
    default:
        return;
    case 0:
        size = sizeof(NormalFish);
        break;
    case 1:
        size = sizeof(UpDownFish);
        break;
    }
    (*fish) = SDL_realloc(*fish, size);

    (*fish)->state = ALIVE;
    (*fish)->x     = speed > 0 ? -FISH_SIZE : WINDOW_WIDTH + FISH_SIZE;
    (*fish)->y     = SDL_rand(WINDOW_HEIGHT - WATER_Y - 70) + WATER_Y + 10;
    (*fish)->speed = speed;

    switch (random_fish_type) {
    default:
        return;
    case 0:
        normal_fish_new(*fish);
        break;
    case 1:
        up_down_fish_new(*fish);
        break;
    }
}
