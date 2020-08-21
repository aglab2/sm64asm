#include "invi_wall_fixer.h"
extern "C"
{
    #include <game/print.h>
    #include <game/object_helpers.h>
    #include <engine/surface_load.h>
}

void InviWallFixer::Init()
{
    oCollisionDistance = 300000.f;
    obj_scale(2.f);
}

void InviWallFixer::Step()
{
    auto diff = gMarioObject->oPosY - oPosY;
    if (diff > 100.f)
        load_object_collision_model();
}

uintptr_t InviWallFixer::Behavior[] = {
    0x0c000000, (uintptr_t) sInit,
    0x2a000000, 0x2004A0A,
    0x08000000,
    0x0c000000, (uintptr_t) sStep,
    0x09000000,
};