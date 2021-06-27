#include "cits_rotat.h"
extern "C"
{
    #include "engine/surface_load.h"
}

static float absf(float x)
{
    return x < 0 ? -x : x;
}

void CITSRotat::Step()
{
    if (absf(oPosY - gMarioObject->oPosY) < 3550.f) 
        load_object_collision_model();
}

uintptr_t CITSRotat1::Behavior[] = 
{
    0x2A000000, 0x07072FF0,
    0x11010001,
    0x10240080,
    0x0E431800,
    0x08000000,
    0x0F130080,
    0x0C000000, (uintptr_t) CITSRotat::sStep,
    0x09000000,
};

uintptr_t CITSRotat2::Behavior[] = 
{
    0x2A000000, 0x07076F70,
    0x11010001,
    0x10240080,
    0x0E431800,
    0x08000000,
    0x0F130080,
    0x0C000000, (uintptr_t) CITSRotat::sStep,
    0x09000000,
};