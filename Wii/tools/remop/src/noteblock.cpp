#include "noteblock.h"

#include <sm64.h>
#include <inputs.h>

void NoteBlock()
{
    auto mario = M64_MARIO_OBJ_PTR;
    auto marioStr = M64_MARIO_STRUCT;
    auto me = M64_CURR_OBJ_PTR;

    if (mario->collide_obj_ptr == me)
    {
        // !!! NB glitch is here :)
        auto spd = 200.0f;
        if (M64_CONTROLLER1_BUTTONS_HOLD & BUTTON_A)
        {
            SpawnObj(me, 0, 0x13000e24);
            SpawnObj(me, 0, 0x13000a98);
            int magic = 0x42800000 + 0x10000 * me->behav_param3;
            spd = *(float*)&magic;
        }
        // No more frame perfect BS :)
        if (M64_CONTROLLER1_BUTTONS_PRESS & BUTTON_B)
            spd = 0.0f;

        marioStr->action = 0x03000881;
        marioStr->speed.y = spd;
        me->pos.y -= 100.0f;
    }

    if (me->pos.y != me->posInit.y)
    {
        me->pos.y += 10.0f;
    }
}