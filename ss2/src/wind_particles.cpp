#include "wind_particles.h"
extern "C"
{
    #include "game/object_helpers.h"
    #include "engine/behavior_script.h"
    #include "engine/math_util.h"
}
#include "ctl.h"

void WindParticles::Init()
{
    f32 d;
    oWindParticlesCtlObject = obj_find_nearest_object_with_behavior((const BehaviorScript*) 0x408000, &d);
}

void WindParticles::Step()
{
    s16 sp2E = 500;
    f32 sp28 = 1.0f;
    if (oTimer == 0) {
        oOpacity = 100;
        if (oMoveAnglePitch == 0) {
            translate_object_xz_random(this, 900.0f);
            oPosX += sins(oMoveAngleYaw + 0x8000) * sp2E; // NOP as Pitch is 0
            oPosY += 80.0f + random_f32_around_zero(200.0f);
            oPosZ += coss(oMoveAngleYaw + 0x8000) * sp2E; // -coss(a) * sp2E
            oMoveAngleYaw += random_f32_around_zero(4000.0f);
            oForwardVel = RandomFloat() * 70.0f + 50.0f;
        } else {
            translate_object_xz_random(this, 600.0f);
            if (oWindParticlesCtlObject->oCtlState)
            {
                oPosY += sp2E - 200; // 300
            }
            else
            {
                oPosY -= sp2E - 200; // 300
            }
            oMoveAngleYaw = RandomU16();
            oForwardVel = 10.0f;
        }
        obj_set_billboard(this);
        obj_scale(sp28);
    }

    if (oWindParticlesCtlObject->oCtlState)
    {
        oVelY = -2 * (RandomFloat() * 30.0f + 50.0f);
    }
    else
    {
        oVelY = RandomFloat() * 30.0f + 50.0f;
    }
    if (oTimer > 8)
    {
        activeFlags = 0;
    }
    oFaceAnglePitch += 4000.0f + 2000.0f * RandomFloat();
    oFaceAngleYaw += 4000.0f + 2000.0f * RandomFloat();
    obj_move_using_fvel_and_gravity();
}

uintptr_t WindParticles::Behavior[] = 
{
    0x11010001,
    0x0C000000, (uintptr_t) sInit,
    0x08000000,
    0x0C000000, (uintptr_t) sStep,
    0x09000000,
};