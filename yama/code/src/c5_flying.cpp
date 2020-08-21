#include "c5_flying.h"
extern "C"
{
    #include "game/level_update.h"
    #include "game/object_helpers.h"
    #include "game/mario.h"
    #include "game/camera.h"
    #include "sm64.h"
}

constexpr float xMin = 1237.f;
constexpr float xMax = 4832.f;
constexpr float zMin = -544.f;
constexpr float zMax = 2829.f;
constexpr float yMin = 4900.f;

constexpr float yTrigger = 5000.f;

#define oWasBoosted OBJECT_FIELD_S32(0x1b)

void C5Flying::Step()
{
    if (xMin > gMarioObject->oPosX || gMarioObject->oPosX > xMax)
        return;
    if (yMin > gMarioObject->oPosY)
        return;
    if (zMin > gMarioObject->oPosZ || gMarioObject->oPosZ > zMax)
        return;

    if (gMarioObject->oPosY < yTrigger)
    {
        oWasBoosted = true;
        set_mario_action(gMarioStates, ACT_JUMP, 0);
        gMarioStates->vel[1] = 120.f;
        set_camera_mode(gCamera, CAMERA_MODE_8_DIRECTIONS, 1);
    }

    if (gMarioStates->floorHeight == gMarioStates->pos[1])
    {
        oWasBoosted = false;
    }
}

uintptr_t C5Flying::Behavior[] = {
    0x08000000,
    0x0c000000, (uintptr_t) sStep,
    0x09000000,
};