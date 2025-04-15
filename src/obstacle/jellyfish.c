#include <fish/fish.h>
#include <game_logic.h>
#include <obstacle/jellyfish.h>

static const Uint32 COLOR = 0x7EA3DE;

void jellyfish_move(Obstacle* obstacle, unsigned long delta_time) {
    Jellyfish* self = (Jellyfish*) obstacle;
    self->base.x += delta_time * self->base.speed;
}

void jellyfish_action(void* context) {
    GameContext* ctx = (GameContext*) context;

    ctx->caught_fish->state = RELEASED;
    ctx->caught_fish        = 0;
    ctx->is_line_cut        = 1;
}

void jellyfish_new(Obstacle* obstacle) {
    Jellyfish* self = (Jellyfish*) obstacle;

    self->base.color          = COLOR;
    self->base.move           = jellyfish_move;
    self->base.perform_action = jellyfish_action;
}
