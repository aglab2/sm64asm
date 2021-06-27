#include "arrow_hour.h"
extern "C"
{
    #include "game/object_helpers.h"
    #include "game/print.h"
}

#include "ctl.h"

void ArrowHour::Init()
{
    f32 d;
    oArrowCtlObject = obj_find_nearest_object_with_behavior((const BehaviorScript*) 0x408000, &d);
    obj_scale(0.45f);
}

void ArrowHour::Step()
{
    if (oArrowCtlObject->oCtlState)
    {
        oFaceAngleRoll += 2 * 0x40;
    }
    else
    {
        oFaceAngleRoll -= 0x20;
    }
}

uintptr_t ArrowHour::Behavior[] = 
{
    0x11010001,
    0x0C000000, (uintptr_t) sInit,
    0x08000000,
    0x0C000000, (uintptr_t) sStep,
    0x09000000,
};