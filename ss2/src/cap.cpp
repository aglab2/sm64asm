extern "C"
{
    #include "types.h"
    #include "game/sound_init.h"
    #include "game/print.h"
    #include "game/area.h"
}

void onCapStep(u16 seqArgs)
{
    if (0x1f != gCurrLevelNum)
        play_cap_music(seqArgs);
}
