#include "b3f_platform.h"
extern "C"
{
    #include "game/level_update.h"
    #include "game/object_helpers.h"
}

void B3FPlatform::Init()
{
    oDrawingDistance = 10000000.f;
    oCollisionDistance = 10000000.f;
}

uintptr_t B3FPlatform::Behavior[] = 
{
    0x2a000000, 0x07000A40,
    0x0c000000, (uintptr_t) sInit,
    0x08000000,
    0x0c000000, 0x803839cc,
    0x09000000,
};