#include "block.h"
extern "C"
{
    #include "game/object_helpers.h"
    #include "engine/surface_load.h"
}
#include "ctl.h"
#include "rm.h"

void Block::Init()
{
    f32 d;
    oBlockCtlObject = obj_find_nearest_object_with_behavior((const BehaviorScript*) 0x408000, &d);
}

void Block::Step()
{
    if (oBlockCtlObject->oCtlState ^ oBehParams2ndByte)
    {
        obj_enable_rendering();
        obj_unhide();
        obj_become_tangible();
        load_object_collision_model();
    }
    else
    {
        obj_disable_rendering();
        obj_become_intangible();
    }
}

uintptr_t Block::Behavior[] = 
{
    0x11010001,
    0x2a000000, BLOCK_COLL_PTR,
    0x0C000000, (uintptr_t) sInit,
    0x08000000,
    0x0C000000, (uintptr_t) sStep,
    0x09000000,
};