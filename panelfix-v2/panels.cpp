#include "types.h"
extern "C"
{
    #include "game/memory.h"
    #include "game/obj_behaviors.h"
    #include "game/object_helpers.h"
    #include "game/object_list_processor.h"
    #include "game/print.h"
}
#include "object_fields.h"

void onPanelStarSpawnedLoop()
{
    auto behaviorAddr = (uintptr_t*) segmented_to_virtual((const void *) 0x130005D8);
    auto listHead = &gObjectListArray[9];
    auto obj = (struct Object *) listHead->next;

    // Check if there are any panels that are unpressed
    while (obj != (struct Object *) listHead) 
    {
        if (obj->behavior == behaviorAddr && obj->activeFlags != 0) 
        {
            if (0 == obj->oAnimState)
                return;
        }

        obj = (struct Object *) obj->header.next;
    }

    gCurrentObject->activeFlags = 0;
    create_star(gCurrentObject->oPosX, gCurrentObject->oPosY, gCurrentObject->oPosZ);
}
