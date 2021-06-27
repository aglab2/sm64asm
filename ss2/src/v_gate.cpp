#include "v_gate.h"

extern "C"
{
    #include "game/object_helpers.h"
}
#include "ctl.h"
#include "object_fields.h"

#include "rm.h"
#include "v.h"

void VGate::Init()
{
    vanishInit(this);
    oCollisionDistance = 900.f;
    oDrawingDistance = 10000.f;
}

void VGate::Step()
{
    vanishStep(this);
}

uintptr_t VGate::Behavior[] = 
{
    0x11010001,
    0x2a000000, VANISH_GATE_COLL_PTR,
    0x0C000000, (uintptr_t) sInit,
    0x08000000,
    0x0C000000, (uintptr_t) sStep,
    0x09000000,
};