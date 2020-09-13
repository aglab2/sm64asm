#include "types.h"

extern "C"
{
    #include "game/level_update.h"
}

#include "cfg.h"
#include "level_reset.h"
#include "savestate.h"
#include "input_viewer.h"
#include "text_manager.h"

#define PLAY_MODE_NORMAL 0
#define PLAY_MODE_PAUSED 2

void onFrame()
{
    if (PLAY_MODE_PAUSED == sCurrPlayMode)
    {
        SaveState::onPause();
        Config::onPause();
    }
    if (PLAY_MODE_NORMAL == sCurrPlayMode)
    {
        SaveState::onNormal();
        InputViewer::onNormal();
        LevelReset::onNormal();
    }

    TextManager::onFrame();
}

uintptr_t _start[] = {
    (uintptr_t) onFrame,
};
