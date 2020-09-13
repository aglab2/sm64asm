#include "switchblock.h"
#include <sm64.h>

#define CONTROL (char*)0x80400000
#define defscale damage_to_mario

void SwitchBlock()
{
    auto me = M64_CURR_OBJ_PTR;
    if (!me->action)
    {
        me->action = 1;
        *CONTROL = me->bparam1;
    }
    
    me->model = me->behav_param3;
    if (me->behav_param3 == *CONTROL)
    {
        ProcessCollision();
    }
    else
    {
        me->model++;
    }
    
}

void SwitchForSwitchBlock()
{
    auto mario = M64_MARIO_OBJ_PTR;
    auto me = M64_CURR_OBJ_PTR;
    me->model = me->behav_param3;

    if (mario->collide_obj_ptr == me && (me->action / 2) != *CONTROL)
    {
        *CONTROL = me->action * 2;
        PlaySoundProperly(0x303b0081);
    }

    auto targetscale = (me->action / 2 == *CONTROL) ? 0.095703125f : 1.0f;
    me->scaling.y = me->scaling.y + 0.19921875f * (targetscale - me->scaling.y);

    ProcessCollision();
}