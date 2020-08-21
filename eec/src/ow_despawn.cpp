#include "ow_despawn.h"
extern "C"
{
    #include "game/level_update.h"
    #include "game/object_helpers.h"
}

void OWDespawn::Init()
{
    activeFlags = 0;
    if (gMarioStates->numStars < 20)
    {
        f32 d;
        auto obj = obj_find_nearest_object_with_behavior((const BehaviorScript*) 0x1300075C, &d);
        if (obj)
            obj->activeFlags = 0;
    }
}

uintptr_t OWDespawn::Behavior[] = 
{
    0x0c000000, (uintptr_t) sInit,
    0x08000000,
    0x09000000,
};