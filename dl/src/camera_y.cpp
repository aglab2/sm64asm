#include "camera_y.h"
extern "C"
{
    #include <game/camera.h>
    #include <game/level_update.h>
}

static void cameraApproachY(struct Camera* c, f32 goalHeight)
{
    f32 approachRate = 20.f;
    f32 snappiness = 20.f;
    approachRate += ABS(c->pos[1] - goalHeight) / snappiness;
    approach_camera_height(c, goalHeight, approachRate);
}

void cameraApproachYLakitu(void* _ctx)
{
    struct StackCtx
    {
        struct Camera* c;
        f32 goalHeight;
    };
    auto ctx = (StackCtx*) _ctx;

    struct Camera* c = ctx->c;
    f32 goalHeight = ctx->goalHeight;
    cameraApproachY(c, goalHeight);
}

void cameraApproachYMario(struct Camera* c, f32 goalHeight)
{
    f32 limit = gMarioStates->pos[1] - 200.f;
    if (goalHeight < limit)
        goalHeight = limit;

    cameraApproachY(c, goalHeight);
}
