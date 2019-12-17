#include "menudraw.h"
#include <sm64.h>

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

#define X_SEGSIZE 120

static inline int GetX(int column)
{
    if (column == 0 || column == 1)
        return X_OFFSET + column * X_SIZE;
    else 
        return X_OFFSET + X_SIZE / 2;
}

static inline int GetY(int line)
{
    return Y_OFFSET - Y_SIZE * line;
}

static void DrawStr(int line, int off, u8* str)
{
    PrintGenericText(off, GetY(line), str);
}

static void DrawSegment(int line, int segment)
{
    u8 segmentStr[] = { 0x1C, 0x0E, 0x0C, 0x1D, 0x12, 0x18, 0x17, 0x9E, 0x01, 0xFF };
    Int2Str(segment, segmentStr + 8);
    DrawStr(line, 128, segmentStr);
}

enum Levels
{
    EX = -1,
    OverWorld = 0,
    Bowser1 = 16,
    Bowser2 = 17,
    Bowser3 = 18,
    Slide = 19,
    MetalCap = 20,
    WingCap = 21,
    VanishCap = 22,
    Rainbow = 23,
    Aquarium = 24,
    EndCake = 25,
};

u8 sideCoursesNames[][3] = {
    { 0x0b, 0x01, 0xff }, // 16=b1
    { 0x0b, 0x02, 0xff }, // 17=b2
    { 0x0b, 0x03, 0xff }, // 18=b3
    
    { 0x18, 0x1c, 0xff }, // slide

    { 0x16, 0x0c, 0xff }, // mc
    { 0x20, 0x0c, 0xff }, // wc
    { 0x1f, 0x0c, 0xff }, // vc
    
    { 0x1d, 0x1d, 0xff }, // rainbow
    { 0x22, 0x1c, 0xff }, // aquarium
    { 0x16, 0x14, 0xff }, // end cake
};

u8 overworldName[] = { 0x18, 0x20, 0xff }; // 23=ow
u8 exName[] = { 0x0E, 0x21, 0xFF }; // 23=ow

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
        Int2Str(val, str + 1);
    }
    else
    {
        Int2Str(val, str);
    }
    str[2] = 0xff;
}

static int DrawStarLine(int line, int column, int level, int shownMask = 0xff)
{
    int x = GetX(column);
    int y = GetY(line);

    if (level == -1)
    {
        PrintGenericText(x, y, exName);
    }
    else if (level == 0)
    {
        PrintGenericText(x, y, overworldName);
    }
    else if (level <= 15)
    {
        u8 levelStr[3] = {};
        SPrintInt2(levelStr, level);
        PrintGenericText(x, y, levelStr);
    }
    else
    {
        PrintGenericText(x, y, sideCoursesNames[level - 16]);
    }
    x += NAME_OFFSET;
    
    int file = SaveFile_GetStarFlags(gCurrSaveFileNum - 1, level - 1);
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
        PrintGenericText(x, y, starStr);
    }

    return CountStars(maskedFile);
}

int DrawCannonLine(int line, u8* str, int level)
{
    int x = GetX(0) + 20;
    int y = GetY(line);
    
    PrintGenericText(x, y, str);

    x += NAME_OFFSET + 140;
    
    int file = SaveFile_GetStarFlags(gCurrSaveFileNum - 1, level - 1);
    bool on = file & (1 << 7);
    u8 starStr[] = { 0xff, 0xff };
    starStr[0] = on ? 0xfa : 0xfd;
    PrintGenericText(x, y, starStr);

    return CountStars(on);
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
        gDPSetEnvColor(gDisplayListHead++, 0, 255, 0, gPauseMenuTranslucency);
    }
    DrawStr(2, 100, collectedStarsStr);
    if (cur == max)
    {
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gPauseMenuTranslucency);
    }
}

void DrawSegment1()
{
    DrawSegment(6, 1);

    int starCount = 0;
    starCount += DrawStarLine(8, 0, 1, 0b11111110);
    starCount += DrawStarLine(9, 0, 2);
    starCount += DrawStarLine(10, 0, 3);
    starCount += DrawStarLine(11, 0, 4);
    
    starCount += DrawStarLine(8,  1, OverWorld, 0b11100000);
    starCount += DrawStarLine(9,  1, EndCake);
    starCount += DrawStarLine(10, 1, MetalCap);
    starCount += DrawStarLine(11, 1, Bowser1);

    DrawStarCount(starCount, 58);
}

void DrawSegment2()
{
    DrawSegment(6, 2);

    int starCount = 0;
    starCount += DrawStarLine(8, 0, 5);
    starCount += DrawStarLine(9, 0, 6);
    starCount += DrawStarLine(10, 0, 7);
    starCount += DrawStarLine(11, 0, 8);
    
    starCount += DrawStarLine(8,  1, OverWorld, 0b00011100);
    starCount += DrawStarLine(9,  1, VanishCap);
    starCount += DrawStarLine(10, 1, WingCap);
    starCount += DrawStarLine(11, 1, Bowser2);
    
    DrawStarCount(starCount, 59);
}

void DrawSegment3()
{
    DrawSegment(6, 3);

    int starCount = 0;
    starCount += DrawStarLine(8, 2, 9);
    starCount += DrawStarLine(9, 2, 10);
    starCount += DrawStarLine(10,  2, Slide);
    starCount += DrawStarLine(11, 2, Bowser3, 0b11111110);
    
    DrawStarCount(starCount, 31);
}

void DrawSegment4()
{
    DrawSegment(6, 4);

    int starCount = 0;
    starCount += DrawStarLine(8, 2, 11);
    starCount += DrawStarLine(9, 2, 12);
    starCount += DrawStarLine(10, 2, OverWorld, 0b00000011);
    starCount += DrawStarLine(11, 2, Rainbow);
    
    DrawStarCount(starCount, 26);
}

void DrawSegment5()
{
    DrawSegment(6, 5);

    int starCount = 0;
    starCount += DrawStarLine(8, 2, 13);
    starCount += DrawStarLine(9, 2, 14);
    starCount += DrawStarLine(10, 2, Aquarium);
    
    DrawStarCount(starCount, 24);
}

void DrawSegment6()
{
    DrawSegment(6, 6);

    int starCount = 0;
    starCount += DrawStarLine(8, 2, 15);
    starCount += DrawStarLine(9, 2, -1, 0b11000000);
    
    {
        u8 desc[] = { 0x0C, 0x0A, 0x17, 0x17, 0x18, 0x17, 0x9E, 0x12, 0x17, 0x9E,
                      0x01, 0x1C, 0x1D, 0x9E, 0x18, 0x1F, 0x0E, 0x1B, 0x20, 0x18, 0x1B, 0x15, 0x0D, 0xFF };
        starCount += DrawCannonLine(10, desc, 1);
    }

    {
        u8 desc[] = { 0x0C, 0x0A, 0x17, 0x17, 0x18, 0x17, 0x9E, 0x12, 0x17, 0x9E,
                      0x0B, 0x18, 0x20, 0x1C, 0x0E, 0x1B, 0x9E, 0x02, 0xFF };
        starCount += DrawCannonLine(11, desc, Bowser3);
    }
    
    DrawStarCount(starCount, 12);
}