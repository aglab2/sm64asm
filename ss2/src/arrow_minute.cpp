#include "arrow_minute.h"
extern "C"
{
    #include "game/object_helpers.h"
    #include "game/print.h"
}

#include "ctl.h"

void ArrowMinute::Init()
{
    f32 d;
    oArrowCtlObject = obj_find_nearest_object_with_behavior((const BehaviorScript*) 0x408000, &d);
    obj_scale(0.6f);
}

void ArrowMinute::Step()
{
    if (oArrowCtlObject->oCtlState)
    {
        oFaceAngleRoll += 2 * 0x180;
    }
    else
    {
        oFaceAngleRoll -= 0x180;
    }
}

uintptr_t ArrowMinute::Behavior[] = 
{
    0x11010001,
    0x0C000000, (uintptr_t) sInit,
    0x08000000,
    0x0C000000, (uintptr_t) sStep,
    0x09000000,
};