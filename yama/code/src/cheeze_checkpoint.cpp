#include "cheeze_checkpoint.h"
extern "C"
{
    #include <game/camera.h>
    #include <game/game.h>
    #include <game/level_update.h>
    #include <game/object_helpers.h>
    #include <game/print.h>
}

enum Actions
{
    INIT,
    WARP,
};

void CheezeCheckPoint::Step()
{
    spawn_object(this, 0, (const BehaviorScript*) 0x13002af0);
    if (oDistanceToMario < 150.f)
    {
        print_text_centered(160, 20, "PRESS L TO WARP BACK HERE");
    }

    if (oAction == INIT)
    {
        if (oDistanceToMario < 150.f)
        {
            oAction = WARP;
        }
    }
    else
    {
        if (gControllers->buttonPressed & L_TRIG && gMarioStates->action != 0x00880898)
        {
            gMarioStates->pos[0] = oPosX;
            gMarioStates->pos[1] = oPosY;
            gMarioStates->pos[2] = oPosZ;
            set_camera_mode(gCamera, CAMERA_MODE_8_DIRECTIONS, 1);
        } 
    }
}

uintptr_t CheezeCheckPoint::Behavior[] = {
    0x11010040,
    0x08000000,
    0x0c000000, (uintptr_t) sStep,
    0x09000000,
};