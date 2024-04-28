#include "menudraw.h"
#include "types.h"
extern "C"
{
    #include "game/ingame_menu.h"
    #include "game/level_update.h"
    #include "game/game.h"
    #include "game/save_file.h"
}

enum LineType
{
    String,
    Star
};

// line starts from 10 pixel, distance=15, max=14
// line is 01 SSSSSSSS; len=11, pixellen=88

#define X_SIZE 108
#define X_OFFSET (240 / 2 - X_SIZE / 2 - 16)
#define Y_OFFSET 218
#define Y_SIZE 15
#define COLOR_YELLOW_R 255
#define COLOR_YELLOW_G 235
#define COLOR_YELLOW_B 20
#define COLOR_BLUE_R 0
#define COLOR_BLUE_G 107
#define COLOR_BLUE_B 247

#define X_SEGSIZE 120

static inline int GetX(int column)
{
    if (column == 0 || column == 1)
        return X_OFFSET + column * X_SIZE;
    else if (column == 2)
        return X_OFFSET + X_SIZE / 2;
    else
        return column;
}

static inline int GetY(int line)
{
    return Y_OFFSET - Y_SIZE * line;
}

static void DrawStr(int line, int off, const u8* str)
{
    print_generic_string(off, GetY(line), str);
}

static void DrawOW1(int line)
{
    static const u8 segmentStr[] = { 0x02, 0x17, 0x0d, 0x9e, 0x0f, 0x15, 0x18, 0x18, 0x1b, 0xFF };
    DrawStr(line, 125, segmentStr);
}

static void DrawOW2(int line)
{
    static const u8 segmentStr[] = { 0x01, 0x1c, 0x1d, 0x9e, 0x0f, 0x15, 0x18, 0x18, 0x1b, 0xFF };
    DrawStr(line, 128, segmentStr);
}

static void DrawOW3(int line)
{
    static const u8 segmentStr[] = { 0x0c, 0x0a, 0x1c, 0x1d, 0x15, 0x0e, 0x9E, 0x10, 0x1b, 0x18, 0x1e, 0x17, 0x0d, 0x1c, 0xFF };
    DrawStr(line, 112, segmentStr);
}

static void DrawOW4(int line)
{
    static const u8 segmentStr[] = { 0x01, 0x1c, 0x1d, 0x9e, 0x0b, 0x0a, 0x1c, 0x0e, 0x16, 0x0e, 0x17, 0x1d, 0xFF };
    DrawStr(line, 118, segmentStr);
}

static void DrawOW5(int line)
{
    static const u8 segmentStr[] = { 0x02, 0x17, 0x0d, 0x9e, 0x0b, 0x0a, 0x1c, 0x0e, 0x16, 0x0e, 0x17, 0x1d, 0xFF };
    DrawStr(line, 115, segmentStr);
}

static void DrawOW6(int line, int column)
{
    gDPSetEnvColor(gDisplayListHead++, 255, 0, 0, gDialogTextAlpha);
    static const u8 segmentStr[] = { 0x0f, 0x12, 0x1b, 0x0e, 0x9e, 0x0f, 0x12, 0x0e, 0x15, 0x0d, 0xFF };
    DrawStr(line, column, segmentStr);
}

static void DrawS(int line, int column)
{
    gDPSetEnvColor(gDisplayListHead++, 131, 0, 255, gDialogTextAlpha);
    static const u8 segmentStr[] = { 0x1c, 0x12, 0x15, 0x0e, 0x17, 0x0c, 0x0e, 0xFF };
    DrawStr(line, column, segmentStr);
}

static void DrawDW(int line, int column)
{
    gDPSetEnvColor(gDisplayListHead++, 56, 220, 0, gDialogTextAlpha);
    static const u8 segmentStr[] = { 0x0d, 0x0e, 0x0a, 0x1d, 0x11, 0x9e, 0x20, 0x12, 0x17, 0x0d, 0xFF };
    DrawStr(line, column, segmentStr);
}

static void DrawCom(int line, int column)
{
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
    static const u8 segmentStr[] = { 0x0c, 0x18, 0x16, 0x0b, 0x12, 0x17, 0x0e, 0x0d, 0xFF };
    DrawStr(line, column, segmentStr);
}

static void DrawF(int line, int column)
{
    gDPSetEnvColor(gDisplayListHead++, 97, 195, 224, gDialogTextAlpha);
    static const u8 segmentStr[] = { 0x0f, 0x0a, 0x1b, 0x0e, 0x20, 0x0e, 0x15, 0x15, 0xFF };
    DrawStr(line, column, segmentStr);
}

static void Draw0Star(int line)
{
    s32 flags = save_file_get_flags();
    gDPSetEnvColor(gDisplayListHead++, 0, 255, 255, gDialogTextAlpha);
    static const u8 desc0[] = { 0x19, 0x0a, 0x1e, 0x1c, 0x12, 0x17, 0x10, 0x9e, 0x0a, 0x15, 0x1b, 0x0e, 0x0a, 0x0d, 0x22, 0x3f, 0x3f, 0x3f, 0x9e, 0x10, 0x0e, 0x1d, 0x9e, 0x01, 0x9e, 0x1c, 0x1d, 0x0a, 0x1b, 0x9e, 0x0f, 0x12, 0x1b, 0x1c, 0x1d, 0xFF};
    static const u8 descK[] = { 0x1C, 0x19, 0x0E, 0x0E, 0x0D, 0x1B, 0x1E, 0x17, 0x9E, 0x1D, 0x12, 0x16, 0x0E, 0xFF };
    if ((flags & (0x000010 | 0x000040)) || (flags & (0x000020 | 0x000080)) || (flags & 0x000200))
    {
        DrawStr(line, 114, descK);
        gDPSetEnvColor(gDisplayListHead++, 255, 0, 200, gDialogTextAlpha);
    }
    else
    {
        DrawStr(line, 58, desc0);
        gDPSetEnvColor(gDisplayListHead++, 255, 0, 0, gDialogTextAlpha);
    }
}

enum Levels
{
    OW = 0,
    B1 = 16,
    B2 = 17,
    B3 = 18,
    Slide = 19,
    MC = 20,
    WC = 21,
    VC = 22,
    Rainbow = 23,
    Aquarium = 24,
    EndCake = 25,
    XOW = 56,
    X1 = 57,
    X2 = 58,
    X3 = 59,
    X4 = 60,
    X5 = 61,
    X6 = 62,
    X7 = 63,
    X8 = 64,
    X9 = 65,
    X10 = 66,
    X11 = 67,
    X12 = 68,
    X13 = 69,
    X14 = 70,
    X15 = 71,
    XB1 = 72,
    XB2 = 73,
    XB3 = 74,
    XSlide = 75,
    XMC = 76,
    XWC = 77,
    XVC = 78,
    XRainbow = 79,
    XAquarium = 80,
    XEnd = 81,
};

static const u8 sideCoursesNames[][3] = {
    { 0x00, 0x01, 0xff }, 
    { 0x00, 0x02, 0xff }, 
    { 0x00, 0x03, 0xff }, 
    { 0x00, 0x04, 0xff }, 
    { 0x00, 0x05, 0xff }, 
    { 0x00, 0x06, 0xff }, 
    { 0x00, 0x07, 0xff }, 
    { 0x00, 0x08, 0xff }, 
    { 0x00, 0x09, 0xff }, 
    { 0x01, 0x00, 0xff }, 
    { 0x01, 0x01, 0xff }, 
    { 0x01, 0x02, 0xff }, 
    { 0x01, 0x03, 0xff }, 
    { 0x01, 0x04, 0xff }, 
    { 0x01, 0x05, 0xff }, 
    { 0x0b, 0x01, 0xff }, // 16=b1
    { 0x9e, 0x9e, 0xff }, // 17=b2
    { 0x0b, 0x03, 0xff }, // 18=b3
    
    { 0x1c, 0x16, 0xff }, // slide

    { 0x9e, 0x9e, 0xff }, // mc
    { 0x9e, 0x9e, 0xff }, // wc
    { 0x9e, 0x9e, 0xff }, // vc
    
    { 0x9e, 0x9e, 0xff }, // rainbow
    { 0x0b, 0x1b, 0xff }, // aquarium
    { 0x9e, 0x9e, 0xff }, // end cake
};

static const u8 overworldName[] = { 0x18, 0x20, 0xff }; // 23=ow

#define NAME_OFFSET 20

static int CountStars(int file)
{
    int cnt = 0;
    for (int i = 0; i <= 7; i++)
    {
        if (file & (1 << i))
            cnt++;
    }

    return cnt;
}

static void SPrintInt2(u8* str, int val)
{
    if (val < 10)
    {
        str[0] = 0x0;
        int_to_str(val, str + 1);
    }
    else
    {
        int_to_str(val, str);
    }
    str[2] = 0xff;
}

static int DrawStarLine(int line, int column, int level, int shownMask = 0xff)
{
    int x = GetX(column);
    int y = GetY(line);

    if ((level == 0) || (level == 56))
    {
        print_generic_string(x, y, overworldName);
    }
    else if (level >= 57)
    {
        print_generic_string(x, y, sideCoursesNames[level - 57]);
    }
    else
    {
        print_generic_string(x, y, sideCoursesNames[level - 1]);
    }
    x += NAME_OFFSET;
    
    int file = 0;

    if (level >= 56)
    {
        file = save_file_get_star_flags(0x100 | (gCurrSaveFileNum - 1), level - 57);
    }
    else
    {
        file = save_file_get_star_flags(gCurrSaveFileNum - 1, level - 1);
    }
    
    int maskedFile = 0;

    for (int i = 0; i <= 7; i++, x+=10)
    {
        int starMask = 1 << (7 - i);
        bool shown = shownMask & starMask;
        if (!shown)
        {
            continue;
        }

        bool on = file & (1 << i);
        if (on)
            maskedFile |= 1 << i;

        u8 starStr[] = { 0xff, 0xff };
        starStr[0] = on ? 0xfa : 0xfd;
        print_generic_string(x, y, starStr);
    }

    return CountStars(maskedFile);
}

void DrawStarCount(int cur, int max)
{
    u8 collectedStarsStr[] = { 0x00, 0x01, 0x9E, 0x18, 0x1E, 0x1D, 0x9E, 0x18, 0x0F, 0x9E, 0x00, 0x00, 0x9E, 0x1C, 0x1D, 0x0A, 0x1B, 0x1C, 0xFF };
    SPrintInt2(collectedStarsStr + 0, cur);
    SPrintInt2(collectedStarsStr + 10, max);
    collectedStarsStr[2] = 0x9e;
    collectedStarsStr[12] = 0x9e;

    if (cur == max)
    {
        gDPSetEnvColor(gDisplayListHead++, 0, 255, 0, gDialogTextAlpha);
    }
    else
    {
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
    }
    DrawStr(3, 100, collectedStarsStr);
}

void DrawKey(int line, int column, int bowser)
{
    int hex1 = 0;
    int hex2 = 0;
    u8 Key[] = { 0xf7, 0xFF};
    s32 flags = save_file_get_flags();

    if(bowser == 1)
    {
        hex1 = 0x000010;
        hex2 = 0x000040;
    }
    else 
    {
        hex1 = 0x000020;
        hex2 = 0x000080;
    }

    if (flags & (hex1 | hex2))
    {
        gDPSetEnvColor(gDisplayListHead++, 255, 229, 104, gDialogTextAlpha);
    }
    else
    {
        gDPSetEnvColor(gDisplayListHead++, 120, 120, 120, gDialogTextAlpha);
    }
    DrawStr(line, column, Key);
}

void DrawSwitch(int line, int column, int color)
{
    int hex = 0;
    int YSoffset = 9;
    u8 Switch[] = { 0xf9, 0xFF};
    s32 flags = save_file_get_flags();
    if (!(flags & 0x000200 /*MOAT*/))
    {
        YSoffset = 0;
    }

    if(color == 0)
    {
        hex = 0x000002;
        YSoffset = 0;
        gDPSetEnvColor(gDisplayListHead++, 255, 0, 0, gDialogTextAlpha);
    }
    else if(color == 1)
    {
        hex = 0x000004;
        gDPSetEnvColor(gDisplayListHead++, 0, 255, 0, gDialogTextAlpha);
    }
    else if(color == 2)
    {
        hex = 0x000008;
        gDPSetEnvColor(gDisplayListHead++, 0, 0, 255, gDialogTextAlpha);
    }
    else
    {
        hex = 0x000200;
        YSoffset = 0;
        gDPSetEnvColor(gDisplayListHead++, 220, 220, 220, gDialogTextAlpha);
    }

    if (!(flags & hex))
    {
        gDPSetEnvColor(gDisplayListHead++, 120, 120, 120, gDialogTextAlpha);
        DrawStr(line, (column+YSoffset), Switch);
    }
    else
    {
        DrawStr(line, (column+YSoffset), Switch);
    }
}

void DrawBoxInicator(int line, int column, int level, int target)
{
      s32 flags = save_file_get_flags();
    if (!(flags & 0x000200 /*MOAT*/))
        return;
    u8 fullbox[] = { 0xe2, 0xFF};

    const s32 targetFlags = target;
    s32 starFlagsY = save_file_get_star_flags((gCurrSaveFileNum - 1), level - 1);
    s32 starFlagsB = save_file_get_star_flags(0x100 | (gCurrSaveFileNum - 1), level - 57);

    if((level == VC)||(level == XVC))
    {
        gDPSetEnvColor(gDisplayListHead++, 131, 0, 255, gDialogTextAlpha);
    }
    else
    {
        gDPSetEnvColor(gDisplayListHead++, 56, 220, 0, gDialogTextAlpha);
    }

    if(level >= 56)
    {
        if ((starFlagsB & targetFlags) == targetFlags)
        {
            DrawStr(line, column, fullbox);
        }
        else
        {
            gDPSetEnvColor(gDisplayListHead++, 120, 120, 120, gDialogTextAlpha);
            DrawStr(line, column, fullbox);
        }
    }
    else
    {
        if ((starFlagsY & targetFlags) == targetFlags)
        {
            DrawStr(line, column, fullbox);
        }
        else
        {
            gDPSetEnvColor(gDisplayListHead++, 120, 120, 120, gDialogTextAlpha);
            DrawStr(line, column, fullbox);
        }
    }
}

void DrawSegment1()
{
    if (gMarioStates->numStars == 0)
    {
        Draw0Star(3);
        {
            static const u8 desc[] = { 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0xFF};
            DrawStr(6, 120, desc);
            DrawStr(10, 120, desc);
        }
        {
            static const u8 desc[] = { 0x21, 0x21, 0x21, 0x21, 0xFF};
            DrawStr(7, 148, desc);
        }
        {
            static const u8 desc[] = { 0x21, 0x21, 0x21,  0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0xFF};
            DrawStr(8, 120, desc);
            DrawStr(9, 120, desc);
        }
        {
            static const u8 desc[] = { 0x21, 0x21, 0xFF};
            DrawStr(11, 120, desc);
            DrawStr(11, 162, desc);
        }
        gDPSetEnvColor(gDisplayListHead++, 0, 0, 255, gDialogTextAlpha);
        {
            static const u8 desc[] = { 0x21, 0x21, 0x21, 0x21, 0xFF};
            DrawStr(7, 120, desc);
        }
    }
    else
    {
        DrawOW1(2);
        int starCount = 0;
        gDPSetEnvColor(gDisplayListHead++, COLOR_YELLOW_R, COLOR_YELLOW_G, COLOR_YELLOW_B, gDialogTextAlpha);

        starCount += DrawStarLine(6, 2, 0, 0b01000010);
        starCount += DrawStarLine(7, 0, 10, 0b11111110);
        starCount += DrawStarLine(8, 0, 11, 0b11111110);
        starCount += DrawStarLine(9, 0, 12, 0b11111110);
        starCount += DrawStarLine(10, 0, 13, 0b11111110);
        starCount += DrawStarLine(7, 1, 14, 0b11111110);
        starCount += DrawStarLine(8, 1, 15, 0b11111110);
        starCount += DrawStarLine(9, 1, Aquarium, 0b11110000);
        starCount += DrawStarLine(10, 1, B3, 0b01000000);
        gDPSetEnvColor(gDisplayListHead++, 131, 0, 255, gDialogTextAlpha);
        {
            static const u8 desc[] = { 0x0F, 0x12, 0x17, 0x0A, 0x15, 0x9E, 0x0B, 0x18, 0x1C, 0x1C, 0xFF};
            DrawStr(6, 194, desc);
        }

        DrawStarCount(starCount, 49);
        DrawBoxInicator(9, 140, MC, 0b10000);
        DrawBoxInicator(10, 140, MC, 0b100000);
        DrawStarCount(starCount, 49);
    }
}

void DrawSegment2()
{
    DrawOW2(2);
    int starCount = 0;
    gDPSetEnvColor(gDisplayListHead++, COLOR_YELLOW_R, COLOR_YELLOW_G, COLOR_YELLOW_B, gDialogTextAlpha);

    starCount += DrawStarLine(7, 0, 1, 0b11111110);
    starCount += DrawStarLine(8, 0, 2, 0b11111110);
    starCount += DrawStarLine(9, 0, 3, 0b11111110);
    starCount += DrawStarLine(10, 0, 4, 0b11111110);
    starCount += DrawStarLine(7, 1, Slide, 0b11110000);
    starCount += DrawStarLine(8, 1, WC, 0b11000000);
    {
        static const u8 desc[] = { 0x20, 0x0c, 0xFF};
        DrawStr(8, 158, desc);
    }
    starCount += DrawStarLine(9, 1, B1, 0b01000000);

    DrawStarCount(starCount, 35);
    DrawBoxInicator(7, 140, VC, 0b10);
    DrawBoxInicator(8, 140, VC, 0b100);
    DrawBoxInicator(10, 140, VC, 0b1000);
    DrawSwitch(8, 198, 0);
    DrawKey(9, 177, 1);
}

void DrawSegment3()
{
    s32 flags = save_file_get_flags();
    DrawOW3(2);
    int starCount = 0;
    int MaxStars = 11;
    gDPSetEnvColor(gDisplayListHead++, COLOR_YELLOW_R, COLOR_YELLOW_G, COLOR_YELLOW_B, gDialogTextAlpha);

    starCount += DrawStarLine(6, 2, 0, 0b10000100);
    starCount += DrawStarLine(8, 2, 5, 0b11111110);
    starCount += DrawStarLine(9, 64, WC, 0b00001100);
    {
        static const u8 desc[] = { 0x1f, 0x0c, 0xFF};
        DrawStr(9, 104, desc);
    }
    if ((gMarioStates->numStars >= 94) || (flags & 0x000200))
    {
        MaxStars = 12;
        starCount += DrawStarLine(10, 44, WC, 0b00000010);
        {
            static const u8 desc[] = { 0x10, 0x1c, 0xFF};
            DrawStr(10, 104, desc);
        }
        DrawSwitch(10, 134, 3);
    }

    DrawStarCount(starCount, MaxStars);
    DrawBoxInicator(6, 184, VC, 0b1);
    DrawBoxInicator(9, 143, MC, 0b1000);
    DrawSwitch(9, 143, 2);
}

void DrawSegment4()
{
    DrawOW4(2);
    int starCount = 0;
    int MaxStars = 33;
    gDPSetEnvColor(gDisplayListHead++, COLOR_YELLOW_R, COLOR_YELLOW_G, COLOR_YELLOW_B, gDialogTextAlpha);
    if (gMarioStates->numStars <= 140)
    {
        starCount += DrawStarLine(6, 2, 0, 0b00110000);
    }
    else
    {
        starCount += DrawStarLine(6, 2, 0, 0b00111000);
        MaxStars = 34;
    }
    starCount += DrawStarLine(7, 0, 6, 0b11111110);
    starCount += DrawStarLine(8, 0, 7, 0b11111110);
    starCount += DrawStarLine(9, 0, 8, 0b11111110);
    starCount += DrawStarLine(10, 0, 9, 0b11111110);
    starCount += DrawStarLine(8, 138, WC, 0b00110000);
    {
        static const u8 desc[] = { 0x16, 0x0c, 0xFF};
        DrawStr(8, 158, desc);
    }
    starCount += DrawStarLine(9, 1, B2, 0b01000000);
    {
        static const u8 desc[] = { 0x0b, 0x02, 0xFF};
        DrawStr(9, 158, desc);
    }

    DrawStarCount(starCount, MaxStars);
    DrawBoxInicator(6, 174, MC, 0b1);
    DrawBoxInicator(7, 140, VC, 0b10000);
    DrawBoxInicator(8, 140, VC, 0b100000);
    DrawBoxInicator(10, 140, MC, 0b100);
    DrawBoxInicator(8, 198, MC, 0b10);
    DrawSwitch(8, 198, 1);
    DrawKey(9, 177, 2);
}

void DrawSegment5()
{
    DrawOW5(2);
    int starCount = 0;
    int MaxStars = 12;
    int YMover = 1;

    if (gMarioStates->numStars >= 142)
    {
        gDPSetEnvColor(gDisplayListHead++, COLOR_YELLOW_R, COLOR_YELLOW_G, COLOR_YELLOW_B, gDialogTextAlpha);
        starCount += DrawStarLine(7, 2, VC, 0b00000010);
        starCount += DrawStarLine(9, 2, MC, 0b00000010);
        DrawS(7,50);
        DrawDW(9,50);
        DrawCom(7,124);
        DrawCom(9,124);
        MaxStars = 14;
        YMover = 0;
    }
    if (gMarioStates->numStars >= 144)
    {
        gDPSetEnvColor(gDisplayListHead++, COLOR_YELLOW_R, COLOR_YELLOW_G, COLOR_YELLOW_B, gDialogTextAlpha);
        starCount += DrawStarLine(11, 2, Rainbow, 0b11111100);
        DrawF(11,50);
        MaxStars = 20;
        YMover = 0;
    }

    gDPSetEnvColor(gDisplayListHead++, COLOR_YELLOW_R, COLOR_YELLOW_G, COLOR_YELLOW_B, gDialogTextAlpha);
    starCount += DrawStarLine((6+YMover), 2, VC, 0b11111100);
    starCount += DrawStarLine((8+YMover), 2, MC, 0b11111100);
    DrawS((6+YMover),50);
    DrawDW((8+YMover),50);
    DrawStarCount(starCount, MaxStars);
}

// Blue Stars Segment 6-10 (only show up at 150 stars)

void DrawSegment6()
{
    DrawOW1(2);
    int starCount = 0;
    gDPSetEnvColor(gDisplayListHead++, COLOR_BLUE_R, COLOR_BLUE_G, COLOR_BLUE_B, gDialogTextAlpha);

    starCount += DrawStarLine(7, 0, X10, 0b11111110);
    starCount += DrawStarLine(8, 0, X11, 0b11111110);
    starCount += DrawStarLine(9, 0, X12, 0b11111110);
    starCount += DrawStarLine(10, 0, X13, 0b11111110);
    starCount += DrawStarLine(7, 1, X14, 0b11111110);
    starCount += DrawStarLine(8, 1, X15, 0b11111110);
    starCount += DrawStarLine(9, 1, XAquarium, 0b11111110);
    starCount += DrawStarLine(10, 1, XB3, 0b11111000);

    DrawStarCount(starCount, 54);
    DrawBoxInicator(9, 140, XMC, 0b10000);
    DrawBoxInicator(10, 140, XMC, 0b100000);
}

void DrawSegment7()
{
    DrawOW2(2);
    int starCount = 0;
    gDPSetEnvColor(gDisplayListHead++, COLOR_BLUE_R, COLOR_BLUE_G, COLOR_BLUE_B, gDialogTextAlpha);

    starCount += DrawStarLine(7, 0, X1, 0b11111110);
    starCount += DrawStarLine(8, 0, X2, 0b11111110);
    starCount += DrawStarLine(9, 0, X3, 0b11111110);
    starCount += DrawStarLine(10, 0, X4, 0b11111110);
    starCount += DrawStarLine(7, 1, XSlide, 0b11111110);
    starCount += DrawStarLine(8, 1, XWC, 0b11000000);
    {
        static const u8 desc[] = { 0x20, 0x0c, 0xFF};
        DrawStr(8, 158, desc);
    }
    starCount += DrawStarLine(9, 1, XB1, 0b11111000);

    DrawStarCount(starCount, 42);
    DrawBoxInicator(7, 140, XVC, 0b10);
    DrawBoxInicator(8, 140, XVC, 0b100);
    DrawBoxInicator(10, 140, XVC, 0b1000);
}

void DrawSegment8()
{
    DrawOW3(2);
    int starCount = 0;
    gDPSetEnvColor(gDisplayListHead++, COLOR_BLUE_R, COLOR_BLUE_G, COLOR_BLUE_B, gDialogTextAlpha);

    starCount += DrawStarLine(6, 2, XOW, 0b11111110);
    starCount += DrawStarLine(8, 2, X5, 0b11111110);
    starCount += DrawStarLine(9, 64, XWC, 0b00001100);
    {
        static const u8 desc[] = { 0x1f, 0x0c, 0xFF};
        DrawStr(9, 104, desc);
    }
    starCount += DrawStarLine(10, 44, XWC, 0b00000010);
    {
        static const u8 desc[] = { 0x10, 0x1c, 0xFF};
        DrawStr(10, 104, desc);
    }

    DrawStarCount(starCount, 17);
    DrawBoxInicator(6, 194, XVC, 0b1);
    DrawBoxInicator(9, 143, XMC, 0b1000);
}

void DrawSegment9()
{
    DrawOW4(2);
    int starCount = 0;
    gDPSetEnvColor(gDisplayListHead++, COLOR_BLUE_R, COLOR_BLUE_G, COLOR_BLUE_B, gDialogTextAlpha);

    starCount += DrawStarLine(7, 0, X6, 0b11111110);
    starCount += DrawStarLine(8, 0, X7, 0b11111110);
    starCount += DrawStarLine(9, 0, X8, 0b11111110);
    starCount += DrawStarLine(10, 0, X9, 0b11111110);
    starCount += DrawStarLine(8, 138, XWC, 0b00110000);
    {
        static const u8 desc[] = { 0x16, 0x0c, 0xFF};
        DrawStr(8, 158, desc);
    }
    {
        static const u8 desc[] = { 0x18, 0x20, 0xff};
        DrawStr(6, 134, desc);
    }
    starCount += DrawStarLine(9, 1, XB2, 0b11111000);
    {
        static const u8 desc[] = { 0x0b, 0x02, 0xFF};
        DrawStr(9, 158, desc);
    }

    DrawStarCount(starCount, 35);
    DrawBoxInicator(6, 154, XMC, 0b1);
    DrawBoxInicator(7, 140, XVC, 0b10000);
    DrawBoxInicator(8, 140, XVC, 0b100000);
    DrawBoxInicator(10, 140, XMC, 0b100);
    DrawBoxInicator(8, 198, XMC, 0b10);
}

void DrawSegment10()
{
    DrawOW5(2);
    int starCount = 0;
    int MaxStars = 13;
    int YMover = 1;
    int YMover2 = 1;

    if (gMarioStates->numStars >= 311)
    {
        gDPSetEnvColor(gDisplayListHead++, COLOR_BLUE_R, COLOR_BLUE_G, COLOR_BLUE_B, gDialogTextAlpha);
        starCount += DrawStarLine(7, 2, XVC, 0b00000010);
        starCount += DrawStarLine(9, 2, XMC, 0b00000010);
        DrawS(7,50);
        DrawDW(9,50);
        DrawCom(7,124);
        DrawCom(9,124);
        MaxStars = 15;
        YMover = 0;
    }
    if (gMarioStates->numStars >= 313)
    {
        gDPSetEnvColor(gDisplayListHead++, COLOR_BLUE_R, COLOR_BLUE_G, COLOR_BLUE_B, gDialogTextAlpha);
        starCount += DrawStarLine(11, 2, XRainbow, 0b11111100);
        DrawF(11,50);
        MaxStars = 21;
        YMover = 0;
        YMover2 = 0;
    }

    gDPSetEnvColor(gDisplayListHead++, COLOR_BLUE_R, COLOR_BLUE_G, COLOR_BLUE_B, gDialogTextAlpha);
    starCount += DrawStarLine((6+YMover), 2, XVC, 0b11111100);
    starCount += DrawStarLine((8+YMover), 2, XMC, 0b11111100);
    starCount += DrawStarLine((10+YMover2), 70, XB2, 0b00000100);
    DrawS((6+YMover),50);
    DrawDW((8+YMover),50);
    gDPSetEnvColor(gDisplayListHead++, 0, 255, 255, gDialogTextAlpha);
    {
        static const u8 desc[] = { 0x0F, 0x12, 0x1B, 0x1C, 0x1D, 0x9E, 0x0B, 0x15, 0x1E, 0x0E, 0x9E, 0x1C, 0x1D, 0x0A, 0x1B, 0xFF};
        DrawStr((10+YMover2), 50, desc);
    }
    DrawStarCount(starCount, MaxStars);
}

// Final Bonus Level (only show up at 319 stars)

void DrawSegment11()
{
    DrawOW6(2, 127);
    int starCount = 0;
    
    gDPSetEnvColor(gDisplayListHead++, COLOR_YELLOW_R, COLOR_YELLOW_G, COLOR_YELLOW_B, gDialogTextAlpha);
    starCount += DrawStarLine(7, 2, 25, 0b11111100);
    starCount += DrawStarLine(10, 2, 25, 0b00000010);
    gDPSetEnvColor(gDisplayListHead++, COLOR_BLUE_R, COLOR_BLUE_G, COLOR_BLUE_B, gDialogTextAlpha);
    starCount += DrawStarLine(8, 2, 81, 0b11111100);
    starCount += DrawStarLine(10, 114, 81, 0b00000010);
    DrawOW6(7, 50);
    DrawOW6(8, 50);
    DrawOW6(10, 50);
    DrawCom(10,124);

    DrawStarCount(starCount, 14);
}