#include <fish/fish.h>
#include <game_logic.h>
#include <obstacle/barrel.h>

void barrel_move(Obstacle* obstacle, unsigned long delta_time) {
    Barrel* self = (Barrel*) obstacle;
    self->base.x += delta_time * self->base.speed;
}

bool barrel_action_check(Obstacle* self, const void* context, const SDL_FRect* hook_rect) {
    SDL_FRect self_rect = {
        self->x,
        self->y,
        self->w,
        self->h,
    };

    GameContext* ctx = (GameContext*) context;

    return (
            ctx->caught_fish &&
            !ctx->is_line_cut &&
            SDL_HasRectIntersectionFloat(hook_rect, &self_rect)
    );
}

void barrel_action(void* context) {
    GameContext* ctx = (GameContext*) context;

    ctx->caught_fish->state = RELEASED;
    ctx->caught_fish        = 0;
}

void barrel_new(Obstacle* obstacle) {
    Barrel* self = (Barrel*) obstacle;

    self->base.w                     = 100.0f;
    self->base.h                     = 126.8f;
    self->base.texture               = "barrel_obstacle";
    self->base.texture_angle         = 20.0;
    self->base.move                  = barrel_move;
    self->base.should_perform_action = barrel_action_check;
    self->base.perform_action        = barrel_action;
}
