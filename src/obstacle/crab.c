#include <common_defs.h>
#include <game_logic.h>
#include <obstacle/crab.h>

#define CRAB_FIXED_SPEED 0.15f

void crab_move(Obstacle* obstacle, unsigned long delta_time) {
    Crab* self = (Crab*) obstacle;

    const float distance_to_hook = ICE_HOLE_WIDTH / 2.0f;
    if (
            self->state == CRABSTATE_MOVING_FORWARD && (
                self->base.speed > 0.0f && self->base.x > HOOK_X - self->base.w - distance_to_hook
                || self->base.speed < 0.0f && self->base.x < HOOK_X + distance_to_hook
            )
       ) {
        self->base.speed *= -1.0f;
        self->state = CRABSTATE_MOVING_BACKWARD;
    }
    self->base.x += delta_time * self->base.speed;
}

bool crab_action_check(Obstacle* self, const void* context, const SDL_FRect* hook_rect) {
    return false;
}

void crab_action(void* context) {
    GameContext* ctx = (GameContext*) context;

    if (ctx->caught_fish) {
        ctx->caught_fish->state = RELEASED;
        ctx->caught_fish        = 0;
    }
    ctx->is_line_cut = 1;
}

void crab_new(Obstacle* obstacle) {
    Crab* self = (Crab*) obstacle;

    const float assigned_speed = self->base.speed;

    self->base.w                     = 180.0f;
    self->base.h                     = 70.0f;
    self->base.y                     = WATER_Y;
    self->base.speed                 = assigned_speed >= 0.0f ? CRAB_FIXED_SPEED : -CRAB_FIXED_SPEED;
    self->base.texture               = "crab_obstacle";
    self->base.texture_angle         = 0.0;
    self->base.move                  = crab_move;
    self->base.should_perform_action = crab_action_check;
    self->base.perform_action        = crab_action;
    self->state                      = CRABSTATE_MOVING_FORWARD;
}
