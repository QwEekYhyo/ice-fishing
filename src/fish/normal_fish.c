#include <fish/normal_fish.h>

static const Uint32 COLOR = 0xFECA38;

void normal_fish_move(Fish* fish, unsigned long delta_time) {
    NormalFish* self = (NormalFish*) fish;
    self->base.x += delta_time * self->base.speed;
}

void normal_fish_new(Fish* fish) {
    NormalFish* self = (NormalFish*) fish;

    self->base.color = COLOR;
    self->base.move = normal_fish_move;
}
