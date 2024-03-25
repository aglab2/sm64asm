#include "stardisplay.h"

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

    gSPDisplayList(gDisplayListHead++, 0x02011d50);
}