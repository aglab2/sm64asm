#include "stardisplay.h"

#include "menudraw.h"
#include <sm64.h>
#include <ultra/gbi.h>

static char menuPicked = 1;

void StarDisplay()
{
    gSPDisplayList(gDisplayListHead++, 0x02011cc8);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gPauseMenuTranslucency);
    
    HandleMenuScrolling(1, &menuPicked, 1, 6);

    switch (menuPicked)
    {
        case 1: DrawSegment1(); break;
        case 2: DrawSegment2(); break;
        case 3: DrawSegment3(); break;
        case 4: DrawSegment4(); break;
        case 5: DrawSegment5(); break;
        case 6: DrawSegment6(); break;
    }

    gSPDisplayList(gDisplayListHead++, 0x02011d50);
}