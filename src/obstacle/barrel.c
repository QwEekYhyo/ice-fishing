#include <fish/fish.h>
#include <game_logic.h>
#include <obstacle/barrel.h>

static const Uint32 COLOR = 0x4D2708;

void barrel_move(Obstacle* obstacle, unsigned long delta_time) {
    Barrel* self = (Barrel*) obstacle;
    self->base.x += delta_time * self->base.speed;
}

void barrel_action(void* context) {
    GameContext* ctx = (GameContext*) context;

    ctx->caught_fish->state = RELEASED;
    ctx->caught_fish        = 0;
}

void barrel_new(Obstacle* obstacle) {
    Barrel* self = (Barrel*) obstacle;

    self->base.color = COLOR;
    self->base.move  = barrel_move;
    self->base.perform_action = barrel_action;
}
