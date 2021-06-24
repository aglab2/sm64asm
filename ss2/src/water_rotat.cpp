#include "water_rotat.h"

extern "C"
{
    #include "game/object_helpers.h"
}
#include "ctl.h"
#include "object_fields.h"

#include "rm.h"

void WaterRotat::Init()
{
    f32 d;
    oWaterRotatCtlObject = obj_find_nearest_object_with_behavior((const BehaviorScript*) 0x408000, &d);
    oCollisionDistance = 1300.f;
    oDrawingDistance = 10000.f;
}

void WaterRotat::Step()
{
    constexpr int spdPerFrame = 0xb9;

    if (oWaterRotatCtlObject->oCtlState)
    {
        oAngleVelYaw = -spdPerFrame * 2;
    }
    else
    {
        oAngleVelYaw = spdPerFrame;
    }
    
    oFaceAngleYaw += oAngleVelYaw;
}

uintptr_t WaterRotat::Behavior[] = 
{
    0x11010001,
    0x2a000000, WATERROTAT_COLL_PTR,
    0x0C000000, (uintptr_t) sInit,
    0x08000000,
    0x0C000000, (uintptr_t) sStep,
    0x0C000000, 0x803839cc,
    0x09000000,
};