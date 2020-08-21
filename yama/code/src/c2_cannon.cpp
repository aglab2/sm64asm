#include "c2_cannon.h"
extern "C"
{
    #include "game/camera.h"
    #include "game/game.h"
    #include "game/level_update.h"
    #include "game/print.h"
    #include "game/mario.h"
    #include "engine/math_util.h"
    #include "sm64.h"
extern s16 sStatusFlags;
extern f32 sCannonYOffset;
}

#define oPreviousAngle  OBJECT_FIELD_S32(0x1b)
#define oPreviousAngle2 OBJECT_FIELD_S32(0x1c)

void C2Cannon::Init()
{
    oDrawingDistance = 40000.f;
}

void C2Cannon::Step()
{
    switch (oAction)
    {
    case Actions::INIT:
        return Check();
    case Actions::IN_CANNON:
        return InCannon();
    case Actions::SHOOT:
        return Shoot();
    }
}

void C2Cannon::Check()
{
    if (oDistanceToMario > 300.f)
        return;

    oAction = Actions::IN_CANNON;
}

void C2Cannon::InCannon()
{
    if (oTimer == 0)
    {
        set_mario_action(gMarioStates, ACT_JUMP, 0);
        gMarioStates->faceAngle[1] += 0;
    }

    *(triplet*) gMarioStates->pos = oPos;
    gMarioStates->faceAngle[0] = oBehParams2ndByte ? 0x1000 : 0;

    oPreviousAngle2 = oPreviousAngle;
    oPreviousAngle = gMarioStates->faceAngle[1];
    gMarioStates->faceAngle[1] = oFaceAngleYaw + (0x3000 * sins(oTimer * 400));
    
    auto c = gCurrentArea->camera;
    c->mode = CAMERA_MODE_INSIDE_CANNON;
    c->cutscene = 0;
    gLakituState.mode = CAMERA_MODE_INSIDE_CANNON;
    sCannonYOffset = 0.f;

    if (gControllers->buttonPressed & A_BUTTON)
    {
        oAction = Actions::SHOOT;
        set_mario_action(gMarioStates, ACT_SHOT_FROM_CANNON, 0);
    }
}

void C2Cannon::Shoot()
{
    if (oTimer == 0)
    {
        gMarioStates->faceAngle[1] = oPreviousAngle2;
        auto c = gCurrentArea->camera;
        c->mode = CAMERA_MODE_8_DIRECTIONS;
        c->cutscene = 0;
        gLakituState.mode = CAMERA_MODE_8_DIRECTIONS;
    }

    if (gMarioStates->action == ACT_SHOT_FROM_CANNON)
    {
        gMarioStates->faceAngle[0] = oBehParams2ndByte ? 0x1000 : 0;
        triplet direction{ sins(gMarioStates->faceAngle[1]), oBehParams2ndByte ? 0.5f : 0.f, coss(gMarioStates->faceAngle[1]) };
        auto newPos = oPos + direction * 100.f * oTimer;
        *(triplet*) gMarioStates->pos = newPos;
    }

    if (oTimer == 40)
    {
        oAction = Actions::INIT;
    }
}

uintptr_t C2Cannon::Behavior[] = 
{
    0x11010040,
    0x0c000000, (uintptr_t) sInit,
    0x08000000,
    0x0c000000, (uintptr_t) sStep,
    0x09000000,
};