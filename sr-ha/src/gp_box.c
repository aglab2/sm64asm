#include "gp_box.h"

#include "sm64.h"
#include "game/level_update.h"
#include "game/object_helpers2.h"
#include "game/object_list_processor.h"
#include "game/obj_behaviors.h"

static void init()
{
    if (0 == gCurrentObject->oBehParams2ndByte)
        return;

    gCurrentObject->oBehParams = 0;
    if (10 == gCurrentObject->oBehParams2ndByte)
    {
        gCurrentObject->oBehParams = 1 << 24;
    }
    if (11 == gCurrentObject->oBehParams2ndByte)
    {
        gCurrentObject->oBehParams = 2 << 24;
    }

    gCurrentObject->oBehParams2ndByte = 0;
}

static void step()
{
    if (gMarioStates->action != ACT_GROUND_POUND_LAND)
    {
        return;
    }

    if (gCurrentObject->oDistanceToMario < 200.f)
    {
        func_802A3004();
        create_star(gCurrentObject->oPosX, gCurrentObject->oPosY + 200.f, gCurrentObject->oPosZ);
        gCurrentObject->activeFlags = 0;
    }
}

uintptr_t gpBoxBehavior[] = {
    0x11010040,
    0x0C000000, (uintptr_t) init,
    0x08000000,
    0x0C000000, (uintptr_t) step,
    0x09000000,
};
