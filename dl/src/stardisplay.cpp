#include "stardisplay.h"
#include "blue_star_mode.h"
#include "types.h"
extern "C" 
{
    #include "game/game.h"
    #include "game/level_update.h"
    #include "game/ingame_menu.h"
}
#include "menudraw.h"

static s8 menuPicked = 1;

void StarDisplay()
{
    gSPDisplayList(gDisplayListHead++, 0x02011cc8);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
    
    if (gMarioStates->numStars == 0)
    {
        handle_menu_scrolling(1, &menuPicked, 1, 1);
    }
    else if (gMarioStates->numStars <= 93)
    {
        handle_menu_scrolling(1, &menuPicked, 1, 4);
    }
    else if (gMarioStates->numStars <= 149)
    {
        handle_menu_scrolling(1, &menuPicked, 1, 5);
    }
    else if (gMarioStates->numStars <= 318)
    {
        handle_menu_scrolling(1, &menuPicked, 1, 10);
    }
    else
    {
        handle_menu_scrolling(1, &menuPicked, 1, 11);
    }

    switch (menuPicked)
    {
        case 1: DrawSegment1(); break;
        case 2: DrawSegment2(); break;
        case 3: DrawSegment3(); break;
        case 4: DrawSegment4(); break;
        case 5: DrawSegment5(); break;
        case 6: DrawSegment6(); break;
        case 7: DrawSegment7(); break;
        case 8: DrawSegment8(); break;
        case 9: DrawSegment9(); break;
        case 10: DrawSegment10(); break;
        case 11: DrawSegment11(); break;
    }

    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
    if (gMarioStates->numStars >= 333)
    {
        {
            // press l to toggle
            static const u8 Press[] = { 0x19, 0x1B, 0x0E, 0x1C, 0x1C, 0x9E, 0x15, 0x9E, 0x1D, 0x18, 0x9E, 0x1D, 0x18, 0x10, 0x10, 0x15, 0x0E, 0xFF };
            static const u8 BlueMode[] = { 0x0B, 0x15, 0x1E, 0x0E, 0x9E, 0x1C, 0x1D, 0x0A, 0x1B, 0x9E, 0x16, 0x18, 0x0D, 0x0E, 0xFF };
            print_generic_string(20, 30, Press);
            gDPSetEnvColor(gDisplayListHead++, 0, 107, 247, gDialogTextAlpha);
            print_generic_string(20, 14, BlueMode);
        }

        if (sBlueStarModeDisabled)
        {
            // blue star mode disabled
            static const u8 text[] = { 0x0D, 0x12, 0x1C, 0x0A, 0x0B, 0x15, 0x0E, 0x0D, 0xFF};
            gDPSetEnvColor(gDisplayListHead++, 255, 0, 0, gDialogTextAlpha);
            print_generic_string(107, 14, text);
        }
        else
        {
            // blue star mode enabled
            static const u8 text[] = { 0x0E, 0x17, 0x0A, 0x0B, 0x15, 0x0E, 0x0D, 0xFF };
            gDPSetEnvColor(gDisplayListHead++, 0, 255, 0, gDialogTextAlpha);
            print_generic_string(110, 14, text);
        }

        if (gPlayer1Controller->buttonPressed & L_TRIG)
        {
            sBlueStarModeDisabled = !sBlueStarModeDisabled;
        }
    }

    gSPDisplayList(gDisplayListHead++, 0x02011d50);
}