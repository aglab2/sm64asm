#include "dorrie_ctl.h"
extern "C"
{
    #include "game/level_update.h"
    #include "game/object_helpers.h"
    #include "game/print.h"
}

#define oDorrie OBJECT_FIELD_OBJ(0x1b)

void DorrieCtl::Init()
{
    f32 dist;
    oDorrie = obj_find_nearest_object_with_behavior((BehaviorScript*) 0x13004F90, &dist);
}

void DorrieCtl::Step()
{
    oDorrie->oPosX = oPosX;
    oDorrie->oPosY = oPosY;
    oDorrie->oPosZ = oPosZ;
    auto floor = gMarioStates->floor;
    if (floor)
    {
        if (floor->type == 122)
        {
            spawn_object(this, 104, (BehaviorScript*) 0x13004F90);
        }
    }
}

uintptr_t DorrieCtl::Behavior[] = {
    0x0c000000, (uintptr_t) sInit,
    0x08000000,
    0x0c000000, (uintptr_t) sStep,
    0x09000000,
};