#include "timer.h"
extern "C"
{
    #include "game/level_update.h"
    #include "game/print.h"
}
#include "cfg.h"
#include "sm64.h"

void Timer::onFrame()
{
    if (Config::timerShow())
    {
        if (gHudDisplay.flags & HUD_DISPLAY_FLAG_COIN_COUNT)
            gHudDisplay.flags |= HUD_DISPLAY_FLAG_TIMER;
        else
            gHudDisplay.flags &= ~HUD_DISPLAY_FLAG_TIMER;
    }
    else
    {
        gHudDisplay.flags &= ~HUD_DISPLAY_FLAG_TIMER;
    }

    switch (Config::timerStyle())
    {
        case Config::TimerStyle::GRAB:
            if (gMarioStates->action == ACT_FALL_AFTER_STAR_GRAB)
                sTimerRunning = false;
        // passthrough
        case Config::TimerStyle::XCAM:  
            if (gMarioStates->action == ACT_STAR_DANCE_WATER
             || gMarioStates->action == ACT_STAR_DANCE_EXIT)
                sTimerRunning = false;
        break;
    }

    if (Config::timerStopOnCoinStar())
        if (gMarioStates->action == ACT_STAR_DANCE_NO_EXIT)
            sTimerRunning = true;
}