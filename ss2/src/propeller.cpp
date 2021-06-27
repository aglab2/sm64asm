#include "propeller.h"
extern "C"
{
    #include "game/object_helpers.h"
}
#include "ctl.h"

void Propeller::Init()
{
    f32 d;
    oPropellerCtlObject = obj_find_nearest_object_with_behavior((const BehaviorScript*) 0x408000, &d);
}

void Propeller::Step()
{
    int spd = oBehParams2ndByte ? 0x563 : 0xd2;
    if (!oPropellerCtlObject->oCtlState)
    {
        oFaceAngleYaw += spd;
    }
    else
    {
        oFaceAngleYaw += -2 * spd;
    }
}

uintptr_t Propeller::Behavior[] = 
{
    0x11010001,
    0x0C000000, (uintptr_t) sInit,
    0x08000000,
    0x0C000000, (uintptr_t) sStep,
    0x09000000,
};