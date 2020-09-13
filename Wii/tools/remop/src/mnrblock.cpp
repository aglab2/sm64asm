#include "mnrblock.h"
#include <sm64.h>

#define HALF_LOOP_TIME 0x80
#define LOOP_TIME 0x110
#define ROTATION_TIME 0x22

#define STEP_TIME 48
#define SWITCH_TIME 30
#define MAX_SPEED 10.0f


#define NOSWITCH_TIME (STEP_TIME - SWITCH_TIME)

#define PATHS ((char*) 0x80604200)

#define inited damage_to_mario
#define cursor transparency
#define cursor_counter health

enum CMD
{
    MOVE_Z_UP,
    MOVE_Z_DOWN,
    MOVE_X_UP,
    MOVE_X_DOWN,
};

static void GetSpeed(int cmd, float& x, float& z)
{    
    switch (cmd)
    {
        case MOVE_Z_UP:
            x = 0.0f;
            z = MAX_SPEED;
            break;
        case MOVE_Z_DOWN:
            x = 0.0f;
            z = -MAX_SPEED;
            break;
        case MOVE_X_UP:
            x = MAX_SPEED;
            z = 0.0f;
            break;
        case MOVE_X_DOWN:
            x = -MAX_SPEED;
            z = 0.0f;
            break;
    }
}

void MnRBlock()
{
    auto me = M64_CURR_OBJ_PTR;

    // Initializer
    if (!me->inited)
    {
        me->model = me->bparam1;
        me->timer = me->bparam1 * HALF_LOOP_TIME;
        me->cursor_counter = 0;
        me->inited = 1;
    }

    if (me->timer >= LOOP_TIME - 32)
    {
        me->speedRotationPitch = -0x40;
    }

    if (me->timer == LOOP_TIME) 
    {
        me->speedRotationPitch = 0x400;
        me->timer = 0;
    }

    if (me->timer == ROTATION_TIME)
    {
        me->speedRotationPitch = 0;
    }


retry:
    unsigned char cmd = *(PATHS + me->behav_param3 * 0x20 + me->cursor);
    if (cmd > MOVE_X_DOWN)
    {
        me->cursor = 0;
        goto retry;
    }

    unsigned char nextCmd = *(PATHS + me->behav_param3 * 0x20 + me->cursor + 1);
    if (nextCmd > MOVE_X_DOWN)
        nextCmd = *(PATHS + me->behav_param3 * 0x20);

    if (me->cursor_counter < (STEP_TIME - SWITCH_TIME))
    {
        GetSpeed(cmd, me->speed.x, me->speed.z);
    }
    else
    {
        float curX, curZ;
        GetSpeed(cmd, curX, curZ);

        float nextX, nextZ;
        GetSpeed(nextCmd, nextX, nextZ);

        float numerator = (float) (me->cursor_counter - NOSWITCH_TIME) / (float) SWITCH_TIME;

        me->speed.x = nextX * numerator + curX * (1 - numerator);
        me->speed.z = nextZ * numerator + curZ * (1 - numerator);
    }

    me->cursor_counter++;
    if (me->cursor_counter == STEP_TIME)
    {
        me->cursor++;
        me->cursor_counter = 0;
    }
    
    ObjMoveUsingVel();
    ObjRotateFaceAngleUsingVel();
}