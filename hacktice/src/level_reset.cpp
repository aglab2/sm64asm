#include "level_reset.h"
extern "C"
{
    #include "types.h"
    #include "game/game.h"
    #include "game/level_update.h"
    #include "game/envfx_snow.h"
}
#include "cfg.h"

static bool sTimerRunningDeferred = false;

void LevelReset::onNormal()
{
    if (sTimerRunningDeferred)
    {
        sTimerRunningDeferred = false;
        sTimerRunning = true;
    }

    auto action = Config::action();
    if (Config::ButtonAction::LEVEL_RESET == action)
    {
        gMarioStates->health = 0x880;
        gHudDisplay.coins = 0;
        gMarioStates->numCoins = 0;
        sWarpDest.type = 2;
        gSnowParticleCount = 5;
        gHudDisplay.timer = 0;
        sTimerRunning = true;
        sTimerRunningDeferred = true;
    }
    
    if (Config::ButtonAction::LEVEL_RESET_WARP == action)
    {
        gMarioStates->health = 0x880;
        gHudDisplay.coins = 0;
        gMarioStates->numCoins = 0;
        sWarpDest.type = 2;
        sWarpDest.areaIdx = 1;
        sWarpDest.nodeId = 0xa;
        gSnowParticleCount = 5;
        gHudDisplay.timer = 0;
        sTimerRunning = true;
        sTimerRunningDeferred = true;
    }

    if (Config::ButtonAction::ACT_SELECT == action)
    {
        sWarpDest.type = 2;
        sWarpDest.areaIdx = 1;
        sWarpDest.nodeId = 0xa;
        gMarioStates->health = 0x880;
        sCurrPlayMode = 0x4;
        gHudDisplay.timer = 0;
        sTimerRunning = true;
        sTimerRunningDeferred = true;
    }

    auto warp = Config::warpIdAndReset();
    if (warp != LevelConv::PlainLevels::OFF)
    {
        auto sm64lvl = LevelConv::toSM64Level(warp);
        
        sWarpDest.levelNum = (u8) sm64lvl;
        sWarpDest.type = 2;
        sWarpDest.areaIdx = 1;
        sWarpDest.nodeId = 0xa;
        gMarioStates->health = 0x880;
        sCurrPlayMode = 0x4;
        gHudDisplay.timer = 0;
        sTimerRunning = true;
        sTimerRunningDeferred = true;
    }
}
