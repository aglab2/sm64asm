#include "shrinkplatform.h"
#include <sm64.h>

enum State
{
    STATIC = 0,
    SQUISHING = 1,
    SQUISHED = 2,
};

#define SQUISHING_TIME 128
#define SQUISHED_TIME 60

#define inited damage_to_mario

void ShrinkPlatform()
{
    auto mario = M64_MARIO_OBJ_PTR;
    auto me = M64_CURR_OBJ_PTR;

    if (!me->inited)
    {
        SpawnObj(me, 0x97, 0x13002a48);
        me->inited = 1;
    }

    switch (me->action)
    {
        case STATIC:
        {
            if (mario->collide_obj_ptr == me)
            {
                PlaySoundProperly(0x50230081);
                me->action = SQUISHING;
            }
            ProcessCollision();
        }
        break;
        case SQUISHING:
        {
            ScaleObject(1 - (float) me->timer / SQUISHING_TIME);
            if (me->timer == SQUISHING_TIME)
                me->action = SQUISHED;

            ProcessCollision();
        }
        break;
        case SQUISHED:
        {
            if (me->timer == SQUISHED_TIME)
            {
                ScaleObject(1);
                me->action = STATIC;
            }
        }
        break;
    }
}