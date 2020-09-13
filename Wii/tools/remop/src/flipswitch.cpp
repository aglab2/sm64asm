#include "flipswitch.h"
#include <sm64.h>

#define FS_SPAWNER rootObj
#define FS_LAST_STEPPING damage_to_mario
#define FSS_PANEL_COUNT transparency

// 802A8238
void FlipSwitch()
{
    auto mario = M64_MARIO_OBJ_PTR;
    auto me = M64_CURR_OBJ_PTR;
    if (!me->timer)
    {
        me->FS_SPAWNER = FindObject(0x130002A0);
        if (!me->FS_SPAWNER)
            goto fini;

        me->FS_SPAWNER->FSS_PANEL_COUNT++;
    }
    else
    {
        MObject* spawner = me->FS_SPAWNER;
        if (!spawner)
            goto fini;
        if (me->model == 2)
            goto fini;

        // Check if we are done
        if (spawner->action == 1)
        {
            me->model = 2;
            goto fini;
        }

        // Regular mode, model 0 or 1
        auto isStepping = mario->collide_obj_ptr == me;
        if (isStepping && isStepping != me->FS_LAST_STEPPING)
        {
            if (me->model)
                spawner->FSS_PANEL_COUNT++;
            else
                spawner->FSS_PANEL_COUNT--;

            me->model ^= 1;
        }
        me->FS_LAST_STEPPING = isStepping;
    }

fini:
    ProcessCollision();
}

void FlipSwitchSpawner()
{
    MObject* me = M64_CURR_OBJ_PTR;
    if (!me->timer)
        return;

    if (me->action)
    {
        me->active = 0;
        return;
    }

    if (me->FSS_PANEL_COUNT == 0)
    {
        CreateStar(me->pos.x, me->pos.y, me->pos.z);
        me->action = 1;
    }
}