#include "wind_ctl.h"
extern "C"
{
    #include "audio_defines.h"
    #include "audio/external.h"
    #include "game/level_update.h"
    #include "game/mario.h"
    #include "game/object_helpers.h"
    #include "game/print.h"
    #include "engine/behavior_script.h"
    #include "engine/math_util.h"
    #include "sm64.h"
}
#include "ctl.h"

float UpSpeed = 40.f;
float DownSpeed = -60.f;
float Acceleration = 7.f;

void WindCtl::SpawnParticles(s16 pitch, s16 yaw, bool dying) 
{
    s32 i;
    for (i = 0; i < 3; i++) {
        struct Object *wind = spawn_object(gMarioObject, 0x8E, (const BehaviorScript*) 0x40803C);
        wind->oMoveAngleYaw = yaw;
        wind->oMoveAnglePitch = pitch;
    }
    if (dying)
    {
        int animFrame = oTimer % 100;
        if (animFrame == 25 || animFrame == 35) {
            play_sound(SOUND_MARIO_COUGHING3, gMarioState->marioObj->header.gfx.cameraToObject);
        }

        if (animFrame == 50 || animFrame == 58) {
            play_sound(SOUND_MARIO_COUGHING2, gMarioState->marioObj->header.gfx.cameraToObject);
        }

        if (animFrame == 71 || animFrame == 80) {
            play_sound(SOUND_MARIO_COUGHING1, gMarioState->marioObj->header.gfx.cameraToObject);
    }
    }
    else
    {
        play_sound(SOUND_ENV_WIND2, gMarioState->marioObj->header.gfx.cameraToObject);
        oTimer = 22;
    }
}

void WindCtl::Init()
{
    f32 d;
    oWindParticlesCtlObject = obj_find_nearest_object_with_behavior((const BehaviorScript*) 0x408000, &d);
}

void WindCtl::Step()
{
    if (gMarioStates->health < 0x100)
        return;

    if (gMarioStates->floor)
    {
        auto type = gMarioStates->floor->type;
        if (123 == type)
        {
            if (gMarioStates->action != ACT_VERTICAL_WIND)
                drop_and_set_mario_action(gMarioStates, ACT_VERTICAL_WIND, 0);
    
            auto& vel = gMarioStates->vel[1];
            if (oWindParticlesCtlObject->oCtlState)
            {
                vel -= 2 * Acceleration;
                if (vel < DownSpeed)
                    vel = DownSpeed;
            }
            else
            {
                vel += 2 * Acceleration;
                if (vel > UpSpeed)
                    vel = UpSpeed;
            }

            bool dying = false;
            if (gMarioStates->pos[1] < 427)
            {
                gMarioStates->health -= 0x14;
                dying = true;
            }
            if (gMarioStates->pos[1] > 3343)
            {
                gMarioStates->health -= 0x14;
                dying = true;
            }
            SpawnParticles(1, 0, dying);
        }
    }
}

uintptr_t WindCtl::Behavior[] = 
{
    0x0C000000, (uintptr_t) sInit,
    0x08000000,
    0x0C000000, (uintptr_t) sStep,
    0x09000000,
};