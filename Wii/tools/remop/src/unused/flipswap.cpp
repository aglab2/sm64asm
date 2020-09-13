#include "flipswap.h"
#include <sm64.h>

enum State
{
    INIT,
    STATIC,
    MOVING
};

void FlipSwap()
{
    auto me = M64_CURR_OBJ_PTR;
    auto mario = M64_MARIO_STRUCT;

    switch (me->action)
    {
        case INIT:
            me->action = 1;
            SpawnObj(me, 0x30, 0x13002a48);
            return;
        case STATIC:
        {
            if (mario->action & 0x800)
            {
                me->action = MOVING;
                me->prevCollision = (me->z_rotation2 & 0x8000) ? 0x1000 : -0x1000;
            }
            break;
        }
        case MOVING:
        {
            if (me->timer <= 0x7)
            {
                ObjRotateFaceAngleUsingVel();
            }
            else
            {
                if (!(mario->action & 0x800))
                    me->action = STATIC;
            }
        }
    }
}