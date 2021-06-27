#include "locked_box.h"
extern "C"
{
    #include "game/object_helpers.h"
    #include "game/obj_behaviors.h"
    #include "audio/external.h"
}

void LockedBox::Init()
{
    scale_object(this, 1.5f);
    oLockedBoxKeyLeft = 3;
}

void LockedBox::Step()
{
    if (0 == oLockedBoxKeyLeft)
    {
        create_star(oPosX, oPosY, oPosZ);
        activeFlags = 0;
    }
}

uintptr_t LockedBox::Behavior[] = {
    0x0c000000, (uintptr_t) sInit,
    0x2a000000, 0x0707B720,
    0x08000000,
    0x0c000000, (uintptr_t) sStep,
    0x0c000000, 0x803839cc,
    0x09000000,
};