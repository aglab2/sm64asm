#include "b3f_switch.h"
extern "C"
{
    #include "game/level_update.h"
    #include "game/object_helpers.h"
    #include "game/object_helpers2.h"
}

enum Actions
{
    INIT,
    PRESSED
};

void B3FSwitch::Init()
{
    scale_object_xyz(this, 1.5f, 1.5f, 1.5f);
}

void B3FSwitch::Step()
{
    if (oAction == INIT)
    {
        if (obj_is_mario_on_platform())
        {
            ShakeScreen(1);
            scale_object_xyz(this, 1.5f, 0.1f, 1.5f);
            oAction = PRESSED;
        }
    }
}

uintptr_t B3FSwitch::Behavior[] = 
{
    0x11010001,
    0x2A000000, 0x0800C7A8, 
    0x0c000000, (uintptr_t) sInit,
    0x08000000,
    0x0c000000, (uintptr_t) sStep,
    0x0c000000, 0x803839cc,
    0x09000000,
};
