#include "ctl.h"

extern "C"
{
    #include "audio/load.h"
    #include "game/game.h"
    #include "game/level_update.h"
    #include "game/object_helpers.h"
    #include "game/print.h"
void save_file_set_flags(s32 flags);
}
#include "object_fields.h"
#include "combiner.h"

void Ctl::Init()
{
    oCtlState = 0;
    oCtlQSRotatSpeed = 0;
    oCtlHealTimer = 0;
    Combiner::Find();
    save_file_set_flags(1 << 2);
}

void Ctl::Step()
{
    if (gMarioStates->health < 0x100)
        return;

    constexpr int healthDrainRate = 0x18;

    if (gControllers[0].buttonPressed & L_TRIG)
    {
        oCtlState = !oCtlState;
        Combiner::Switch(oCtlState);
    }

    if (oCtlState)
    {
        gSequencePlayers[0].tempo = 3840 * 2;
        if (gMarioStates->health > healthDrainRate)
        {
            oCtlHealTimer++;
            gMarioStates->health -= healthDrainRate;
        }
    }
    else
    {
        gSequencePlayers[0].tempo = 3840;
        if (oCtlHealTimer)
        {
            int healAmount = oCtlHealTimer == 1 ? healthDrainRate : 2 * healthDrainRate;
            if (gMarioStates->health < 2176)
            {
                gMarioStates->health += healAmount;
            }
            else
            {
                gMarioStates->health = 2176;
            }
            
            if (oCtlHealTimer == 1)
            {
                oCtlHealTimer = 0;
            }
            else
            {
                oCtlHealTimer -= 2;
            }
        }
    }

    if (oCtlState)
    {
        gMarioStates->capTimer += 2;
    }

    if (gMarioStates->flags & 0x00000004)
    {
        print_text_fmt_int(20, 20, "%d", gMarioStates->capTimer);
    }
}

uintptr_t Ctl::Behavior[] = 
{
    0x11010001,
    0x0C000000, (uintptr_t) sInit,
    0x08000000,
    0x0C000000, (uintptr_t) sStep,
    0x09000000,
};