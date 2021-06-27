#include "v_wk.h"

extern "C"
{
    #include "game/object_helpers.h"
}
#include "ctl.h"
#include "object_fields.h"

#include "rm.h"
#include "v.h"

void VWk::Init()
{
    vanishInit(this);
    oCollisionDistance = 3000.f;
    oDrawingDistance = 10000.f;
}

void VWk::Step()
{
    vanishStep(this);
}

uintptr_t VWk::Behavior[] = 
{
    0x11010001,
    0x2a000000, VANISH_WK_COLL_PTR,
    0x0C000000, (uintptr_t) sInit,
    0x08000000,
    0x0C000000, (uintptr_t) sStep,
    0x09000000,
};