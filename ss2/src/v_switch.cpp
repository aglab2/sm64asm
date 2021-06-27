#include "v_switch.h"
extern "C"
{
    #include "audio_defines.h"
    #include "audio/external.h"
    #include "game/camera.h"
    #include "game/level_update.h"
    #include "game/object_helpers.h"
    #include "game/object_helpers2.h"
    #include "game/print.h"
}
#include "ctl.h"

void VSwitch::Init()
{
    f32 d;
    oVSwitchCtlObject = obj_find_nearest_object_with_behavior((const BehaviorScript*) 0x408000, &d);
}

// TODO: lazy
void VSwitch::ScaleOverTime(s32 a0, s32 a1, f32 sp10, f32 sp14) 
{
    f32 sp4 = sp14 - sp10;
    f32 sp0 = (f32) oTimer / a1;

    if (a0 & 0x01) {
        header.gfx.scale[0] = sp4 * sp0 + sp10;
    }

    if (a0 & 0x02) {
        header.gfx.scale[1] = sp4 * sp0 + sp10;
    }

    if (a0 & 0x04) {
        header.gfx.scale[2] = sp4 * sp0 + sp10;
    }
}

void VSwitch::Step()
{
    switch (oAction) 
    {
        case PURPLE_SWITCH_IDLE:
            obj_scale(1.5f);
            if (gMarioObject->platform == this) 
            {
                if (lateral_dist_between_objects(this, gMarioObject) < 127.5f) {
                    oAction = PURPLE_SWITCH_PRESSED;
                }
            }
            break;
        case PURPLE_SWITCH_PRESSED:
            ScaleOverTime(2, 3, 1.5f, 0.2f);
            if (oTimer == 3) 
            {
                play_sound(SOUND_GENERAL2_PURPLE_SWITCH, gCurrentObject->header.gfx.cameraToObject);
                oAction = PURPLE_SWITCH_TICKING;
                ShakeScreen(SHAKE_POS_SMALL);
            }
            break;
        /**
         * Play a continuous ticking sound that gets faster when time is almost
         * up. When time is up, move to a waiting-while-pressed state.
         */
        case PURPLE_SWITCH_TICKING:
            gMarioStates->flags &= ~0x00000004;
            print_text_fmt_int(20, 20, "%d", 200 - oVSwitchTimer);
            if (oVSwitchCtlObject->oCtlState)
            {
                if (oVSwitchTimer % 2)
                    oVSwitchTimer++;

                if (oVSwitchTimer)
                    oVSwitchTimer -= 2;
            }
            else
            {
                oVSwitchTimer++;
            }

            if (oVSwitchTimer < 160)
            {
                play_sound(SOUND_GENERAL2_SWITCH_TICK_FAST, gDefaultSoundArgs);
            }
            else if (oVSwitchTimer < 200) 
            {
                play_sound(SOUND_GENERAL2_SWITCH_TICK_SLOW, gDefaultSoundArgs);
            }
            else
            {
                if (gMarioObject->oPosX < 1878 || gMarioObject->oPosZ < -1201)
                {
                    oVSwitchTimer = 0;
                    oAction = PURPLE_SWITCH_IDLE;
                }
                else
                {
                    oVSwitchTimer = 200;
                }
            }
            break;
    }
}

uintptr_t VSwitch::Behavior[] = 
{
    0x102F0001, 
    0x11010001,
    0x2a000000, 0x0800C7A8,
    0x0C000000, (uintptr_t) sInit,
    0x08000000,
    0x0C000000, (uintptr_t) sStep,
    0x0C000000, 0x803839cc,
    0x09000000,
};