#include "sound_farewell.h"
#include "types.h"
extern "C"
{
    #include <game/area.h>
    #include <game/print.h>
    #include <level_table.h>
    extern u8 sCurrentBackgroundMusicSeqId;
    extern void seq_player_play_sequence(u8 player, u8 seqId, u16 arg2);
}

static const u8 kSectionMusic[] = { 0x2, 0x7, 0xc };
static u8 sMusicOverride = 0;
int gLoopCount = 0;
int gMusicOverridePrint = -1;

static int getCurrentSection()
{
    u8 music = sCurrentBackgroundMusicSeqId;
    for (int i = 0; i < 3; i++)
    {
        if (kSectionMusic[i] == music)
        {
            return i;
        }
    }

    // this should never happen
    return -1;
}

void soundPreJmp()
{
    if (gCurrLevelNum != LEVEL_WMOTR)
    {
        return;
    }

    gLoopCount++;
    int wantSection = (gCurrAreaIndex - 1) / 2;
    int currSection = getCurrentSection();
    if (currSection < wantSection)
    {
        sMusicOverride = kSectionMusic[currSection + 1];
        gMusicOverridePrint = sMusicOverride;
    }
}

void soundPostSequence()
{
    if (gCurrLevelNum != LEVEL_WMOTR)
    {
        sMusicOverride = 0;
        return;
    }

    if (sMusicOverride)
        seq_player_play_sequence(0, sMusicOverride, 0);

    sMusicOverride = 0;
}
