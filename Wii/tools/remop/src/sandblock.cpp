#include "sandblock.h"
#include <sm64.h>

enum State
{
    STATIC = 0,
    SQUISHING = 1,
    SQUISHED = 2,
};

#define SQUISHING_TIME 192
#define SQUISHED_TIME 100

#define HEIGHT 303.0

void SandBlock()
{
    auto mario = M64_MARIO_OBJ_PTR;
    auto me = M64_CURR_OBJ_PTR;

    switch (me->action)
    {
        case STATIC:
        {
            if (mario->collide_obj_ptr == me)
            {
                me->action = SQUISHING;
            }
            ProcessCollision();
        }
        break;
        case SQUISHING:
        {
            if (me->timer == 0)
            {
                me->rootObj = SpawnObj(me, 0, 0x13003ca4);
            }

            if (me->timer == SQUISHING_TIME)
            {
                me->rootObj->active = 0;
                me->action = SQUISHED;
            }

            me->pos.y += HEIGHT / SQUISHING_TIME;
            me->scaling.y = 1 - (float) me->timer / (float) SQUISHING_TIME;
            ProcessCollision();
        }
        break;
        case SQUISHED:
        {
            if (me->timer == SQUISHED_TIME)
            {
                me->pos.y -= HEIGHT;
                me->scaling.y = 1;
                me->action = STATIC;
            }
        }
        break;
    }
}