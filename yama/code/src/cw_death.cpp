#include "cw_death.h"
extern "C"
{
    #include "game/game.h"
    #include "game/level_update.h"
    #include "game/object_helpers.h"
    #include "game/print.h"
    
    extern "C" void play_sequence(u8 player, u8 seqId, u16 fadeTimer);
}

enum Actions
{
    INIT,
    DEAD,
};

void CWDeath::Step()
{
    if (oAction == INIT)
    {
        if (oTimer > 200)
        {
            auto y = gMarioStates->pos[1];
            if (y > 9000.f)
            {
                oAction = DEAD;
                oPosY = 10000.f;
                play_sequence(0, 83, 0);
            }
        }
    }
    else
    {
        gMarioStates->pos[1] = oPosY;
        if (oPosY < 19000.f)
            oPosY += 30.f;
        
        oPosX = gMarioStates->pos[0];
        oPosZ = gMarioStates->pos[2];
        gMarioStates->action = 0x03000880;
        spawn_object(this, 0, (const BehaviorScript*) 0x13002af0);

        if (oTimer > 100)
        {
            if (gControllers->buttonPressed & L_TRIG)
            {
                oAction = INIT;
                play_sequence(0, 80, 0);
                gMarioStates->usedObj = this;
                level_trigger_warp(gMarioStates, WARP_OP_WARP_OBJECT);
            }
            print_text_centered(160, 200, "GAME OYER");
            print_text_centered(160, 40, "PRESS L TO RESET");
        }
    }
}

uintptr_t CWDeath::Behavior[] = 
{
    0x08000000,
    0x0c000000, (uintptr_t) sStep,
    0x09000000,
};