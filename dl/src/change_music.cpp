#include "change_music.h"
extern "C"
{
    #include <audio/load.h>
    #include <game/display.h>
    #include <game/game.h>
    #include <game/print.h>
    #include <game/object_helpers.h>
    #include <object_fields.h>

    extern void seq_player_play_sequence(u8 player, u8 seqId, u16 arg2);
    extern u8 sCurrentBackgroundMusicSeqId;
    extern u16 sCurrentShellMusic;
    extern u8 sBgMusicDisabled;
}

static bool sPlayNewMusic = false;
constexpr int kNewMusic = 0x08;
constexpr int kOldMusic = 0x30;

void ChangeMusic::Init()
{
}

void ChangeMusic::Step()
{
    if (0 == gGlobalTimer % 10)
    {
        spawn_object(gCurrentObject, MODEL_NONE, (const BehaviorScript*) 0x13002af0);
    }

    if (gCurrentObject->oDistanceToMario < 200.f && gPlayer1Controller->buttonPressed & L_TRIG)
    {
        sPlayNewMusic = !sPlayNewMusic;
    }

    if (sCurrentShellMusic == 0xffff && sCurrentBackgroundMusicSeqId != 255)
    {
        int music = sPlayNewMusic ? kNewMusic : kOldMusic;
        if (sCurrentBackgroundMusicSeqId != music)
        {
            seq_player_play_sequence(0, music, 0);
        }
    }
}

int ChangeMusic::Behavior[] =
{
    0x11010040, // calc dist to mario
    0x0c000000, (int) sInit,
    0x08000000,
    0x0c000000, (int) sStep,
    0x09000000,
};
