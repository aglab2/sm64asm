#include "types.h"
#include "frame_collision.h"
#include <game/mario.h>
#include <game/object_list_processor.h>

static s32 onFrame()
{
	frame_collision_check();
    return execute_mario_action(gCurrentObject);
}

uintptr_t _start[] = {
    (uintptr_t) onFrame,
};
