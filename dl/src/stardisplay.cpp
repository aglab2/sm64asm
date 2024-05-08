#include "stardisplay.h"
#include "blue_star_mode.h"
#include "types.h"
extern "C" 
{
    #include <level_commands.h>
    #include <game/area.h>
    #include "game/game.h"
    #include "game/level_update.h"
    #include "game/ingame_menu.h"
    #include "game/save_file.h"
}
#include "menudraw.h"

#define YCounter 14
#define X1 4
#define XL1 X1+44
#define X2 120
#define XL2 X2+52
#define X3 245
#define XL3 X3+32
#define XStar 24

static s8 menuPicked = 1;

int SetFloor()
{
    if ((gMarioStates->numStars == 0)
    || (gCurrLevelNum == LEVEL_CASTLE_COURTYARD && gCurrAreaIndex > 1))
        return 1;
    else if ((gCurrLevelNum == LEVEL_CASTLE && gCurrAreaIndex == 1))
        return 2;
    else if ((gCurrLevelNum == LEVEL_CASTLE_GROUNDS && gCurrAreaIndex == 1)
    || (gCurrLevelNum == LEVEL_CASTLE && gCurrAreaIndex == 2))
        return 3;
    else if ((gCurrLevelNum == LEVEL_CASTLE_COURTYARD && gCurrAreaIndex == 1))
        return 4;
    else
        return 5;
}

static void SPrintInt3(u8* str, int val)
{
    int_to_str(val, str);
    str[3] = 0xff;
}

int Offsetter(int val)
{
    if (val >= 100)
        return 0;
    else if (val >= 10)
        return 7;
    else
        return 14;
}

void StarDisplay()
{
    static bool A_Press = true;
    int A_Allowed = 0;
    int AvailableStars = 1;
    int MaxStars = 150;
    int Mover = 0;
    s32 flags = save_file_get_flags();
    gSPDisplayList(gDisplayListHead++, 0x02011cc8);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);

    if (gPlayer1Controller->buttonPressed & R_TRIG)
    {
        A_Press = !A_Press;
    }

    static bool initialized;
    if (!initialized)
    {
        menuPicked = SetFloor();
        initialized = true;
    }

    if ((gPlayer1Controller->buttonPressed & START_BUTTON)||(gPlayer1Controller->buttonPressed & A_BUTTON))
        initialized = false;

    if (gMarioStates->numStars == 0)
    {
        A_Allowed = 0;
        handle_menu_scrolling(1, &menuPicked, 1, 1);
    }
    else if ((flags & 0x000200) && (gMarioStates->numStars < 150))
    {
        A_Allowed = 0;
        handle_menu_scrolling(1, &menuPicked, 1, 5);
    }
    else if (gMarioStates->numStars < 150)
    {
        A_Allowed = 0;
        handle_menu_scrolling(1, &menuPicked, 1, 4);
    }
    else if (gMarioStates->numStars < 319)
    {
        A_Allowed = 1;
        handle_menu_scrolling(1, &menuPicked, 1, 5);
    }
    else
    {
        A_Allowed = 1;
        handle_menu_scrolling(1, &menuPicked, 1, 6);
    }

    if ((A_Allowed == 0) || (A_Press))
    {
        switch (menuPicked)
        {
            case 1: DrawSegment1(); break;
            case 2: DrawSegment2(); break;
            case 3: DrawSegment3(); break;
            case 4: DrawSegment4(); break;
            case 5: DrawSegment5(); break;
            case 6: DrawSegment11(); break;
        }
    }
    else
    {
        switch (menuPicked)
        {
            case 1: DrawSegment6(); break;
            case 2: DrawSegment7(); break;
            case 3: DrawSegment8(); break;
            case 4: DrawSegment9(); break;
            case 5: DrawSegment10(); break;
            case 6: DrawSegment11(); break;
        }
    }

    if (A_Allowed == 1)
    {
        gDPSetEnvColor(gDisplayListHead++, 255, 235, 20, gDialogTextAlpha);
        if (A_Press)
        {
            gDPSetEnvColor(gDisplayListHead++, 0, 107, 247, gDialogTextAlpha);
        }
        static const u8 R_Text[] = { 0x19, 0x1B, 0x0E, 0x1C, 0x1C, 0x9E, 0x1B, 0x9E, 0x0F, 0x18, 0x1B, 0x9E, 0xFa, 0xFF };
        print_generic_string(116, 210, R_Text);
    }

    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
    static const u8 Version[] = { 0x39, 0x01, 0x3F, 0x01, 0xFF };
    print_generic_string(294, 220, Version);

    if (gMarioStates->numStars < 333)
    {

        if (gMarioStates->numStars == 0)
        {
            AvailableStars = 1;
            MaxStars = 150;            
        }
        else if (gMarioStates->numStars >= 150+169)
        {
            AvailableStars = 333;
            MaxStars = 333;
        }
        else if (gMarioStates->numStars >= 150+163)
        {
            AvailableStars = 150+169;
            MaxStars = 333;
        }
        else if (gMarioStates->numStars >= 150+161)
        {
            AvailableStars = 150+163;
            MaxStars = 333;
        }
        else if (gMarioStates->numStars >= 150)
        {
            AvailableStars = 150+161;
            MaxStars = 333;
        }
        else if (gMarioStates->numStars >= 144)
        {
            AvailableStars = 150;
            MaxStars = 150;
        }
        else if (gMarioStates->numStars >= 142)
        {
           AvailableStars = 144;
           MaxStars = 150;
        }
        else if (gMarioStates->numStars == 141)
        {
           AvailableStars = 142;
           MaxStars = 150;
        }
        else if ((flags & 0x000200) && (gMarioStates->numStars < 141))
        {
            AvailableStars = 141;
            MaxStars = 150;
        }
        else if (gMarioStates->numStars >= 94)
        {
            AvailableStars = 129;
            MaxStars = 150;
            gDPSetEnvColor(gDisplayListHead++, 0, 255, 255, gDialogTextAlpha);
            static const u8 Hint[] = { 0x0C, 0x2B, 0x28, 0x26, 0x2E, 0x9E, 0xD1, 0x9E, 0x1C, 0x2B, 0x28, 0x27, 0x9E, 0x29, 0x32, 0x35, 0x9E, 0x24, 0x9E, 0x09, 0x04, 0x9E, 0x1C, 0x37, 0x24, 0x35, 0x9E, 0x0D, 0x32, 0x32, 0x35, 0xFF };
            print_generic_string(70, 220, Hint);
        }
        else if (flags & (0x000020 | 0x000080) && gMarioStates->numStars < 94)
        {
            AvailableStars = 128;
            MaxStars = 150;
        }
        else if (flags & (0x000010 | 0x000040))
        {
            AvailableStars = 79;
            MaxStars = 150;
        }
        else if (!(flags & (0x000010 | 0x000040)) && gMarioStates->numStars <= 34)
        {
            AvailableStars = 34;
        }
        else // more than 0 stars and no keys or gray switch
        {
            AvailableStars = gMarioStates->numStars;
        }

        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
        u8 Number[] = { 0x0, 0x0, 0x0, 0x9E, 0xFF };

        Mover = Offsetter(gMarioStates->numStars);
        SPrintInt3(Number + 0, gMarioStates->numStars);
        Number[3] = 0x9E;
        print_generic_string(XL1 + Mover, YCounter, Number);

        Mover = Offsetter(AvailableStars);
        SPrintInt3(Number + 0, AvailableStars);
        Number[3] = 0x9E;
        print_generic_string(XL2 + Mover, YCounter, Number);

        SPrintInt3(Number + 0, MaxStars);
        Number[3] = 0x9E;
        print_generic_string(XL3, YCounter, Number);

        static const u8 StarIcon[] = { 0xFa, 0x36, 0xFF };
        static const u8 Line1[] = { 0x0C, 0x38, 0x35, 0x35, 0x28, 0x31, 0x37, 0xE6, 0xFF };
        static const u8 Line2[] = { 0x0A, 0x39, 0x24, 0x2C, 0x2F, 0x24, 0x25, 0x2F, 0x28, 0xE6, 0xFF };
        static const u8 Line3[] = { 0x1D, 0x32, 0x37, 0x24, 0x2F, 0xE6, 0xFF };

        print_generic_string(XL1 + XStar, YCounter, StarIcon);
        print_generic_string(XL2 + XStar, YCounter, StarIcon);
        print_generic_string(XL3 + XStar, YCounter, StarIcon);
        print_generic_string(X1, YCounter, Line1);
        print_generic_string(X2, YCounter, Line2);
        print_generic_string(X3, YCounter, Line3);

    }

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