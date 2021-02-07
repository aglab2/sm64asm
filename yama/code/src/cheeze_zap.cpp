#include "cheeze_zap.h"
extern "C"
{
    #include "audio/external.h"
    #include "audio_defines.h"
    #include "game/level_update.h"
}

void CheezeZap::Step()
{
    oDamageOrCoinValue = 1;
    auto timer = oTimer;
    auto offset = oBehParams2;
    timer += offset;
    constexpr auto cycle = 90;
    timer %= cycle;
    auto halfCycle = cycle / 2;

    auto shouldHit = timer < halfCycle;
    auto shouldShow = false;
    if (shouldHit)
    {
        shouldShow = true;
        if (timer > halfCycle - 10)
        {
            auto leftTimer = timer - halfCycle;
            shouldShow = 0 == (leftTimer % 3);
        }
    }

    header.gfx.scale[0] = shouldShow ? 0.75 : 0;
    if (shouldHit)
    {
        // Set Collision sphere size (XZ radius = 192, Y radius = 1024)
        auto x = oPosX - gMarioObject->oPosX;
        auto y = oPosY - gMarioObject->oPosY;
        auto z = oPosZ - gMarioObject->oPosZ;

        if (x * x + z * z < 192 * 192 && -10 < y && y < 1024)
        {
            if (!gMarioStates->invincTimer)
            {
                play_sound(SOUND_MARIO_ATTACKED, gMarioObject->header.gfx.cameraToObject);
                gMarioStates->health -= 0x100;
            }
            gMarioStates->invincTimer = 30;
        }
    }
}

int CheezeZap::Behavior[] = {
    0x11012001,
    0x23000000, 0x00C00400, 
    0x32000048,
    0x08000000,
    0x10050000,
    0x102B0000, 
    0x0c000000, (int) sStep,
    0x09000000,
};
