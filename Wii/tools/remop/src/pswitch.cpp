#include "pswitch.h"
#include <sm64.h>

enum Actions
{
    INIT,
    PRESSING,
    PRESSED,
};

#define PRESSED_TIME 0xd4
#define TIME_PART 7 / 10

static void Switch()
{
    auto coinBehav = SegmentedToVirtual(0x13000934);
    auto boxBehav = SegmentedToVirtual(0x13001500);

    for (MObject* cur = (MObject*) 0x8033D488; cur != (MObject*) 0x80360e88; cur++)
    {
        if (!cur->active)
            continue;

        if (coinBehav == cur->script_ptr)
        {
            SpawnObj(cur, 0x81, 0x130014e0);
            cur->active = 0;
        }
        else if (boxBehav == cur->script_ptr)
        {
            SpawnObj(cur, 0x75, 0x1300090c);
            cur->active = 0;
        }
    }
}

void PSwitch()
{
    auto me = M64_CURR_OBJ_PTR;
    auto mario = M64_MARIO_OBJ_PTR;

    switch (me->action)
    {
    case INIT:
    {
        if (mario->collide_obj_ptr == me)
        {
            me->action = PRESSING;
        }
    }
    break;
    case PRESSING:
    default:
    {
        me->scaling.y = 1.0f - 0.04980469f * me->timer;
        if (me->timer == 0x12)
            me->action = PRESSED;
    }
    break;
    case PRESSED:
    {
        if (me->timer == 0 || me->timer == PRESSED_TIME)
            Switch();
        
        if (me->timer == PRESSED_TIME)
        {
            me->scaling.y = 1;
            me->action = INIT;
        }
            
        if (me->timer < PRESSED_TIME * TIME_PART)
        {
            if (me->timer % 16 == 1 || me->timer % 16 == 4)
                PlaySoundProperly(0x30540081);
        }
        else
        {
            if (me->timer % 3 == 0)
                PlaySoundProperly(0x30540081);
        }
    }
    break;
    }
}