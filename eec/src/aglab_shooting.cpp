#include "aglab_shooting.h"
extern "C"
{
    #include "audio_defines.h"
    #include "game/object_helpers.h"
    #include "game/spawn_sound.h"
    #include "model_ids.h"
}

#define oScale OBJECT_FIELD_S32(0x1b)

constexpr float sShootTime = 6.f;
constexpr float sTargetScale = 1.f;

static void cur_obj_rotate_yaw_toward(s16 target, s16 increment) 
{
    s16 startYaw;

    startYaw = (s16) gCurrentObject->oMoveAngleYaw;
    gCurrentObject->oMoveAngleYaw = approach_s16_symmetric(gCurrentObject->oMoveAngleYaw, target, increment);
}

void AglabShooting::Step()
{
    if (oScale == 0 && oDistanceToMario > 2000.f)
    {
        oScale = 0;
        scale_object(this, sTargetScale);
        return;
    }
    
    obj_turn_toward_object(this, gMarioObject, O_MOVE_ANGLE_PITCH_INDEX, 2000);
    cur_obj_rotate_yaw_toward(oAngleToMario, 2000);

    oScale++;
    if (oScale > sShootTime)
    {
        PlaySound2(SOUND_OBJ_SNUFIT_SHOOT);
        oScale = 0;
        spawn_object_relative(0, 0, -20, 40, this, MODEL_BOWLING_BALL, (const BehaviorScript*) 0x1300521C);
    }
    
    scale_object(this, sTargetScale - oScale / sShootTime * sTargetScale);
}

uintptr_t AglabShooting::Behavior[] = 
{
    0x11012041,
    0x08000000,
    0x0c000000, (uintptr_t) sStep,
    0x09000000,
};