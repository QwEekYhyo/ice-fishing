#include <fish/normal_fish.h>

void normal_fish_move(Fish* fish, unsigned long delta_time) {
    NormalFish* self = (NormalFish*) fish;
    self->base.x += delta_time * self->base.speed;
}

void normal_fish_new(Fish* fish) {
    NormalFish* self = (NormalFish*) fish;

    self->base.w       = 150.0f;
    self->base.h       = 50.0f;
    self->base.texture = "normal_fish";
    self->base.move    = normal_fish_move;
}
