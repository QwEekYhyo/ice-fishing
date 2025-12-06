#include <SDL3/SDL_log.h>
#include <SDL3/SDL_stdinc.h>

#include <common_defs.h>
#include <fish/fish.h>
#include <fish/normal_fish.h>
#include <fish/updown_fish.h>

void move_fish(Fish* fish, unsigned long delta_time) {
    fish->move(fish, delta_time);

    if (
        (fish->speed > 0 && fish->x >= WINDOW_WIDTH) ||
        (fish->speed < 0 && fish->x <= -fish->w)
    )
        fish->state = DEAD;
}

#define FISH_TYPE_NUMBER 2
typedef enum {
    FISHTYPE_NORMAL = 0,
    FISHTYPE_UPDOWN = 1,
} FishType;

// TODO: different probabilities for each type of fish
typedef struct {
    size_t size;
    void (*init)(Fish*);
} FishDesc;

static const FishDesc FISH_DESCS[FISH_TYPE_NUMBER] = {
    [FISHTYPE_NORMAL] = { sizeof(NormalFish), normal_fish_new },
    [FISHTYPE_UPDOWN] = { sizeof(UpDownFish), up_down_fish_new },
};

Fish* spawn_fish(Fish* fish) {
    const float speed = (SDL_randf() * 2.0) - 1.0;

    const Uint8 random_type   = SDL_rand(FISH_TYPE_NUMBER);
    const FishDesc* fish_desc = &FISH_DESCS[random_type];

    void* new_memory = SDL_realloc(fish, fish_desc->size);
    if (!new_memory) {
        SDL_Log("Failed to realloc fish");
        return fish;
    }
    fish = new_memory;

    fish->state = ALIVE;
    fish->y     = SDL_rand(WINDOW_HEIGHT - WATER_Y - 70) + WATER_Y + 10;
    fish->speed = speed != 0 ? speed : 0.1f; // Security just in case

    fish_desc->init(fish);

    fish->x = speed >= 0 ? -fish->w : WINDOW_WIDTH + fish->w;

    return fish;
}
