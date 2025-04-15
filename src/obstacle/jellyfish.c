#include <common_defs.h>
#include <fish/fish.h>
#include <game_logic.h>
#include <obstacle/jellyfish.h>

static const Uint32 COLOR = 0x7EA3DE;

void jellyfish_move(Obstacle* obstacle, unsigned long delta_time) {
    Jellyfish* self = (Jellyfish*) obstacle;
    self->base.x += delta_time * self->base.speed;
}

bool jellyfish_action_check(Obstacle* self, const void* context, const SDL_FRect* hook_rect) {
    SDL_FRect self_rect = {
        self->x,
        self->y,
        OBSTACLE_SIZE,
        OBSTACLE_SIZE,
    };

    SDL_FRect whole_line_rect = {
        hook_rect->x + hook_rect->w / 2,
        WATER_Y,
        .w = 2, // IDK
        .h = hook_rect->y - WATER_Y,
    };

    GameContext* ctx = (GameContext*) context;

    return (
            !ctx->is_line_cut &&
            SDL_HasRectIntersectionFloat(&whole_line_rect, &self_rect)
    );
}

void jellyfish_action(void* context) {
    GameContext* ctx = (GameContext*) context;

    if (ctx->caught_fish) {
        ctx->caught_fish->state = RELEASED;
        ctx->caught_fish        = 0;
    }
    ctx->is_line_cut        = 1;
}

void jellyfish_new(Obstacle* obstacle) {
    Jellyfish* self = (Jellyfish*) obstacle;

    self->base.color                 = COLOR;
    self->base.move                  = jellyfish_move;
    self->base.should_perform_action = jellyfish_action_check;
    self->base.perform_action        = jellyfish_action;
}
