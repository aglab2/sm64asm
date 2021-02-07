#include "beach_2d_ctl.h"
extern "C"
{
    #include "game/game.h"
    #include "game/level_update.h"
    #include "game/print.h"
    #include "audio/external.h"
    
    extern void play_sequence(u8 player, u8 seqId, u16 fadeTimer);
    extern s16 s8DirModeYawOffset;
}

#define oShouldLimitActions OBJECT_FIELD_S32(0x1c)
void BeachTwoDCtl::Init()
{
    oShouldLimitActions = true;
    TwoD::Init();
}

void BeachTwoDCtl::Step()
{
    if (gMarioStates->action == 0x00001302 || gMarioStates->action == 0x00001303 || gMarioStates->action == 0x00001307)
        return;

    if (gMarioStates->action == 0x00001321)
    {
        if (!oShouldLimitActions)
        {
            play_sequence(0, 49, 0);
            oShouldLimitActions = !oShouldLimitActions;
        }
    }

    if (gMarioStates->health < 0xff)
    {
        return;
    }

    if (oShouldLimitActions)
    {
        // auto mask = U_JPAD | D_JPAD | L_JPAD | R_JPAD | U_CBUTTONS | D_CBUTTONS | L_CBUTTONS | R_CBUTTONS | R_TRIG;
        // gControllers->buttonDown    &= (~mask);
        // gControllers->buttonPressed &= (~mask);
        TwoD::Step();
        gMarioStates->health = 0x800;
    }
    else
    {
        if (gMarioStates->health > 0)
            gMarioStates->health -= 0x5;
    }

    if (gControllers[0].buttonPressed & L_TRIG)
    {
        oShouldLimitActions = !oShouldLimitActions;

        if (oShouldLimitActions)
        {
            s8DirModeYawOffset = 0;
            play_sequence(0, 49, 0);
        }
        else
        {
            s8DirModeYawOffset = 0x4000;
            play_sequence(0, 57, 0);
        }
    }
}

int BeachTwoDCtl::Behavior[] = {
    0x0c000000, (int) sInit,
    0x08000000,
    0x0c000000, (int) sStep,
    0x09000000,
};

void BeachTwoDRevert::Step()
{
    if (oDistanceToMario > 450.f)
        return;

    if (gMarioObject->oPosY < oPosY)
    {
        print_text(120, 20, "NOPE");
    }
}

int BeachTwoDRevert::Behavior[] = {
    0x11010040,
    0x08000000,
    0x0c000000, (int) sStep,
    0x09000000,
};

void BeachTwoDMusicFixer::Step()
{
}

int BeachTwoDMusicFixer::Behavior[] = {
    0x08000000,
    0x0c000000, (int) sStep,
    0x09000000,
};
