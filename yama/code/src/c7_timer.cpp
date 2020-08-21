#include "c7_timer.h"
extern "C"
{
    #include "game/level_update.h"
    #include "game/print.h"
}

enum Actions
{
    INIT,
    TICKING,
    FINAL,
};

#define oTime OBJECT_FIELD_S32(0x1b)

static void printTime(int time)
{
    print_text_fmt_int(20, 200, "%02d", time / 30);
    print_text_fmt_int(50, 200, "%02d", (time % 30) * 100 / 30);
}

void C7Timer::Step()
{
    if (oAction == INIT)
    {
        if (!oBehParams1)
        {
            auto x = gMarioStates->pos[0];
            auto y = gMarioStates->pos[1];
            auto z = gMarioStates->pos[2];
            if (6045.f < x || x < 3824.f)
                return;
            if (4595.f < z || z < 2586.f)
                return;
            if (y < -188.f)
                oAction = TICKING;
        }
        else
        {
            auto x = gMarioStates->pos[0];
            if (x > oPosX && x < oPosX + 100.f)
            {
                oAction = TICKING;
            }
        }
    }
    else if (oAction == FINAL)
    {
        printTime(oTime);
    }
    else
    {
        auto targetTime = oBehParams1 ? 200 : 378;
        auto leftTimer = targetTime - oTimer;
        printTime(leftTimer);
        if (leftTimer <= 0)
        {
            oAction = INIT;
            gMarioStates->usedObj = this;
            level_trigger_warp(gMarioStates, WARP_OP_WARP_OBJECT);
        }

        auto action = gMarioStates->action;
        if (action == 0x00001302 || action == 0x00001303 || action == 0x00001307 || action == 0x00001904)
        {
            oTime = leftTimer;
            oAction = FINAL;
        }
    }
}

uintptr_t C7Timer::Behavior[] = {
    0x08000000,
    0x0c000000, (uintptr_t) sStep,
    0x09000000,
};