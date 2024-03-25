#include "ex_objects.h"
#include "types.h"
extern "C"
{
    #include <game/display.h>
    #include <game/object_list_processor.h>
    #include <engine/graph_node.h>
    extern struct GfxPool gGfxPools[2];
}

#pragma GCC diagnostic push
// Complains about the size of gGfxPools not matching sizeof Object. I know this is a hack, shut up
#pragma GCC diagnostic ignored "-Wsizeof-array-div"
#define EXTRA_OBJECTS_COUNT ((sizeof(gGfxPools) / sizeof(Object)) - 3)

void clearObjects()
{
    struct Object* extraObjects = (struct Object*) gGfxPools;

    for (int i = 0; i < OBJECT_POOL_CAPACITY; i++) {
        gObjectPool[i].activeFlags = 0;
        geo_reset_object_node(&gObjectPool[i].header.gfx);
    }
    for (int i = 0; i < EXTRA_OBJECTS_COUNT; i++) {
        auto& obj = extraObjects[i];
        obj.activeFlags = 0;
        geo_reset_object_node(&obj.header.gfx);
    }
}

void initFreeObjectList()
{
    s32 i;
    s32 poolLength = OBJECT_POOL_CAPACITY;
    struct Object* extraObjects = (struct Object*) gGfxPools;

    // Add the first object in the pool to the free list
    struct Object *obj = &gObjectPool[0];
    gFreeObjectList.next = (struct ObjectNode *) obj;

    // Link each object in the pool to the following object
    for (i = 0; i < poolLength - 1; i++) {
        obj->header.next = &(obj + 1)->header;
        obj++;
    }

    for (int i = 0; i < EXTRA_OBJECTS_COUNT; i++) {
        auto& exObj = extraObjects[i];
        obj->header.next = &exObj.header;
        obj = &exObj;
    }

    // End the list
    obj->header.next = nullptr;
}
#pragma GCC diagnostic pop
