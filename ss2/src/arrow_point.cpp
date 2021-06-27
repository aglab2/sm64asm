#include "arrow_point.h"
extern "C"
{
    #include "game/object_helpers.h"
    #include "game/print.h"
}

#include "ctl.h"

static triplet NormalPos{ 1108, 676, -2157 };
static triplet InvertedPos{ 876, 676, -2076 };

void ArrowPoint::Init()
{
    f32 d;
    oArrowCtlObject = obj_find_nearest_object_with_behavior((const BehaviorScript*) 0x408000, &d);
}

void ArrowPoint::Step()
{
    if (!oArrowCtlObject->oCtlState)
    {
        oFaceAngleRoll = 49152;
        oPos = InvertedPos;
    }
    else
    {
        oFaceAngleRoll = 16384;
        oPos = NormalPos;
    }
}

uintptr_t ArrowPoint::Behavior[] = 
{
    0x11010001,
    0x0C000000, (uintptr_t) sInit,
    0x08000000,
    0x0C000000, (uintptr_t) sStep,
    0x09000000,
};