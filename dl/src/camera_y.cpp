#include "camera_y.h"
extern "C"
{
    #include <game/camera.h>
}

void cameraApproachY(void* _ctx)
{
    struct StackCtx
    {
        struct Camera* c;
        f32 goalHeight;
    };
    auto ctx = (StackCtx*) _ctx;

    struct Camera* c = ctx->c;
    f32 goalHeight = ctx->goalHeight;
    f32 approachRate = 20.f;
    approachRate += ABS(c->pos[1] - goalHeight) / 20;
    approach_camera_height(c, goalHeight, approachRate);
}
