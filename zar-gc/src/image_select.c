#include "image_select.h"
#include "render_image.h"
#include "types.h"
#include "levels.h"

#include "audio/internal.h"
#include "game/area.h"
#include "game/display.h"
#include "game/game.h"
#include "game/ingame_menu.h"
#include "game/level_update.h"
#include "engine/math_util.h"

extern s32 save_file_get_star_flags(s32 fileIndex, s32 courseIndex);
extern s16 get_str_x_pos_from_center(s16 centerPos, u8 *str, f32 scale);

enum State
{
    SELECT_STAR,
    SHOW_IMAGE,
};

static int gState = SELECT_STAR;
static int gSelectedStar = 0;
static int gSelectedWarpTarget = 0;

static const u8 uPressBToShowTheHintArt[] = { 0x19, 0x1B, 0x0E, 0x1C, 0x1C, 0x9E, 0x0B, 0x9E, 0x1D, 0x18, 0x9E, 0x1C, 0x11, 0x18, 0x20, 0x9E, 0x1D, 0x11, 0x0E, 0x9E, 0x11, 0x12, 0x17, 0x1D, 0x9E, 0x0A, 0x1B, 0x1D, 0xFF };
static const u8 uPressBToHideTheHint[] = { 0x19, 0x1B, 0x0E, 0x1C, 0x1C, 0x9E, 0x0B, 0x9E, 0x1D, 0x18, 0x9E, 0x11, 0x12, 0x0D, 0x0E, 0x9E, 0x1D, 0x11, 0x0E, 0x9E, 0x11, 0x12, 0x17, 0x1D, 0x9E, 0x0A, 0x1B, 0x1D, 0xFF };
static u8 uHintArtNumber[] = { 0x11, 0x12, 0x17, 0x1D, 0x9E, 0x0A, 0x1B, 0x1D, 0x9E, 0x00, 0x00, 0xFF };
static const u8 uMoveDpad[] = { 0x1E, 0x1C, 0x0E, 0x9E, 0x0D, 0x19, 0x0A, 0x0D, 0x9E, 0x1D, 0x18, 0x9E, 0x1C, 0x0E, 0x15, 0x0E, 0x0C, 0x1D, 0x9E, 0x1D, 0x11, 0x0E, 0x9E, 0x1C, 0x1D, 0x0A, 0x1B, 0x9E, 0x11, 0x12, 0x17, 0x1D, 0xFF };
static const u8 uUp[] = { 0x50, 0xff };
static const u8 uDown[] = { 0x51, 0xff };
static const u8 uLeft[] = { 0x52, 0xff };
static const u8 uRight[] = { 0x53, 0xff };
static const u8 uControlStickToWarpTarget[] = { 0x1E, 0x1C, 0x0E, 0x9E, 0x0C, 0x9E, 0x0B, 0x1E, 0x1D, 0x1D, 0x18, 0x17, 0x1C, 0x9E, 0x18, 0x1B, 0x9E, 0x0C, 0x18, 0x17, 0x1D, 0x1B, 0x18, 0x15, 0x9E, 0x1C, 0x1D, 0x12, 0x0C, 0x14, 0x9E, 0x1D, 0x18, 0x9E, 0x1C, 0x0E, 0x15, 0x0E, 0x0C, 0x1D, 0x9E, 0x20, 0x0A, 0x1B, 0x19, 0x9E, 0x1D, 0x0A, 0x1B, 0x10, 0x0E, 0x1D, 0xFF };
static const u8 uWarpToCourse[] = { 0x19, 0x1B, 0x0E, 0x1C, 0x1C, 0x9E, 0x15, 0x9E, 0x1D, 0x18, 0x9E, 0x20, 0x0A, 0x1B, 0x19, 0x9E, 0x1D, 0x18, 0x9E, 0x0C, 0x18, 0x1E, 0x1B, 0x1C, 0x0E, 0xFF };
static const u8 uThanksForPLaying[] = { 0x1D, 0x11, 0x0A, 0x17, 0x14, 0x9E, 0x22, 0x18, 0x1E, 0x9E, 0x0F, 0x18, 0x1B, 0x9E, 0x19, 0x15, 0x0A, 0x22, 0x12, 0x17, 0x10, 0xFF };
static const u8 uMadeBy[] = { 0x16, 0x0A, 0x0D, 0x0E, 0x9E, 0x0B, 0x22, 0x9E, 0x18, 0x23, 0x23, 0x12, 0x0E, 0x9E, 0x0A, 0x17, 0x0D, 0x9E, 0x0A, 0x10, 0x15, 0x0A, 0x0B, 0x02, 0xFF };

#define dl_ia_text_begin 0x02011cc8
#define dl_ia_text_end   0x02011d50

static u32 sROMPointers[] = {
/* 0 */ 0x01441000,
/* 1 */ 0x014d1000,
/* 2 */ 0x01503000,
/* 3 */ 0x01535000,
/* 4 */ 0x01583000,
/* 5 */ 0x015b5000,
/* 6 */ 0x015e7000,
/* 7 */ 0x019e3000,
/* 8 */ 0x01d90000,
/* 9 */ 0x01dc2000,
/* 10 */ 0x01df4000,
/* 11 */ 0x01f64000,
/* 12 */ 0x02044000,
/* 13 */ 0x02076000,
/* 14 */ 0x020a8000,
/* 15 */ 0x020e3000,
/* 16 */ 0x022b1000,
/* 17 */ 0x022e3000,
/* 18 */ 0x02315000,
/* 19 */ 0x02347000,
/* 20 */ 0x02383000,
/* 21 */ 0x024ce000,
/* 22 */ 0x02623000,
/* 23 */ 0x02655000,
/* 24 */ 0x0272f000,
/* 25 */ 0x02761000,
/* 26 */ 0x02793000,
/* 27 */ 0x0285f000,
/* 28 */ 0x028c3000,
/* 29 */ 0x028f5000,
/* 30 */ 0x02a4d000,
/* 31 */ 0x02bb8000,
/* 32 */ 0x02bea000,
/* 33 */ 0x02f92000,
/* 34 */ 0x02fc4000,
/* 35 */ 0x02ff6000,
/* 36 */ 0x03131000,
/* 37 */ 0x03163000,
};

struct StarInLevelDesc
{
    u8 level;
    u8 starId;
};

static const struct StarInLevelDesc sStarsInLevels[] = {
    { LevelConv_PlainLevels_S2, 0, },
    { LevelConv_PlainLevels_C1, 0, },
    { LevelConv_PlainLevels_C9, 0, },
    { LevelConv_PlainLevels_C6, 0, },
    { LevelConv_PlainLevels_Slide, 0, },
    { LevelConv_PlainLevels_S1, 0, },
    { LevelConv_PlainLevels_C5, 0, },
    { LevelConv_PlainLevels_C14, 0, },
    { LevelConv_PlainLevels_C13, 0, },
    { LevelConv_PlainLevels_C12, 0, },
    { LevelConv_PlainLevels_S3, 0, },
    { LevelConv_PlainLevels_C11, 0, },
    { LevelConv_PlainLevels_WC, 0, },
    { LevelConv_PlainLevels_C7, 0, },
    { LevelConv_PlainLevels_C8, 0, },
    { LevelConv_PlainLevels_MC, 0, },
    { LevelConv_PlainLevels_C5, 1, },
    { LevelConv_PlainLevels_C2, 0, },
    { LevelConv_PlainLevels_C3, 1, },
    { LevelConv_PlainLevels_B1, 0, },
    { LevelConv_PlainLevels_C10, 0, },
    { LevelConv_PlainLevels_B2, 0, },
    { LevelConv_PlainLevels_C5, 2, },
    { LevelConv_PlainLevels_C15, 0, },
    { LevelConv_PlainLevels_C3, 0, },
    { LevelConv_PlainLevels_B3, 0, },
    { LevelConv_PlainLevels_C9, 1, },
    { LevelConv_PlainLevels_C4, 0, },
    { LevelConv_PlainLevels_C1, 1, },
    { LevelConv_PlainLevels_VC, 0, },
};

static void print_generic_string_centered(const u8* str, int x, int y)
{
    s16 rx = get_str_x_pos_from_center(x, (u8*) str, 10.0f);
    print_generic_string(rx, y, str);
}

static void print_generic_string_centered_aligned(const u8* str, int y)
{
    print_generic_string_centered(str, 160, y);
}

extern void dma_read(u8 *dest, u8 *srcStart, u8 *srcEnd);
static void load_image()
{
    u8* ramPtr = (u8 *)0x80026000;
    u8* romPtr = (u8 *)sROMPointers[gSelectedStar];
    u32 imgSize = 0x36000;
    dma_read(ramPtr, romPtr, romPtr + imgSize); 
}

static int has_star(int idx)
{
    struct StarInLevelDesc desc = sStarsInLevels[idx];
    s32 flags = save_file_get_star_flags(gCurrSaveFileNum - 1, desc.level);
    return flags & (1 << desc.starId);
}

static void render_star_select()
{
    print_generic_string_centered_aligned(uPressBToShowTheHintArt, 230-20);
    print_generic_string_centered_aligned(uMoveDpad, 230-34);

    {
        int column = gSelectedStar % 10;
        int row = gSelectedStar / 10;
        if (gPlayer3Controller->buttonPressed & D_JPAD)
        {
            row++;
        }

        if (gPlayer3Controller->buttonPressed & U_JPAD)
        {
            row--;
        }

        if (gPlayer3Controller->buttonPressed & R_JPAD)
        {
            column++;
        }

        if (gPlayer3Controller->buttonPressed & L_JPAD)
        {
            column--;
        }

        row += 3;
        row %= 3;
        column += 10;
        column %= 10;

        gSelectedStar = 10 * row + column;
        
        print_generic_string(25*column + 44, -25*row + 170 - 13, uUp);
        print_generic_string(25*column + 44, -25*row + 170 + 13, uDown);
    }

    // screen size is 320x240. we render 10x5 images, in 10 sized chunks.
    for (int i = 0; i < 30; i++)
    {
        int column = i % 10;
        int row = i / 10;
    
        u8 line[4];
        int_to_str(i + 1, line);
        if (has_star(i))
        {
            gDPSetEnvColor(gDisplayListHead++, 100, 255, 100, gDialogTextAlpha);
        }
        else
        {
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
        }
        print_generic_string_centered(line, 25*column + 47, -25*row + 170);
    }
}

extern struct WarpDest sWarpDest;
static void render_course_select()
{
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
    if (gPlayer3Controller->buttonPressed & U_CBUTTONS)
    {
        gSelectedWarpTarget++;
    }
    
    if (gPlayer3Controller->buttonPressed & D_CBUTTONS)
    {
        gSelectedWarpTarget--;
    }

    gSelectedWarpTarget += 25;
    gSelectedWarpTarget %= 25;

    {
        int controllerDistance = (int)gPlayer3Controller->rawStickX * (int)gPlayer3Controller->rawStickX + (int)gPlayer3Controller->rawStickY * (int)gPlayer3Controller->rawStickY;
        if (controllerDistance > 1000)
        {
            u16 angle = atan2s(gPlayer3Controller->rawStickY, gPlayer3Controller->rawStickX);
            float normalizedAngle = (float) angle / (float) 0x10000;
            gSelectedWarpTarget = (int) (normalizedAngle * 25);
        }
    }

    print_generic_string_centered_aligned(uControlStickToWarpTarget, 85 - 10);
    print_generic_string_centered_aligned(uWarpToCourse, 85 - 14 - 10);

    u8** courseNameTbl = (u8**) segmented_to_virtual((void*) 0x02010f68);
    u8* courseName = (u8*) segmented_to_virtual(courseNameTbl[gSelectedWarpTarget]);
    int off = 40 - 12;
    print_generic_string_centered_aligned(courseName, off);
    print_generic_string_centered_aligned(uUp, off + 15);
    print_generic_string_centered_aligned(uDown, off - 15);

    if (gPlayer3Controller->buttonPressed & L_TRIG)
    {
        gPlayer3Controller->buttonPressed |= START_BUTTON;
        LevelConv_SM64Levels sm64lvl = LevelConv_toSM64Level(gSelectedWarpTarget);
        
        sWarpDest.levelNum = (u8) sm64lvl;
        sWarpDest.type = 2;
        sWarpDest.areaIdx = 1;
        sWarpDest.nodeId = 0xa;
        gMarioStates->health = 0x880;
        sCurrPlayMode = 0x4;
        gHudDisplay.timer = 0;

        if (gSelectedWarpTarget == LevelConv_PlainLevels_C15)
        {
            sWarpDest.areaIdx = 5; 
        }
    }
}

static void switch_star_lr()
{
    int reload = 0;
    if (gPlayer3Controller->buttonPressed & R_JPAD)
    {
        gSelectedStar++;
        reload = 1;
    }

    if (gPlayer3Controller->buttonPressed & L_JPAD)
    {
        gSelectedStar--;
        reload = 1;
    }

    if (reload)
    {
        gSelectedStar += 30;
        gSelectedStar %= 30;
        load_image();
    }
}

extern uintptr_t _start[];
extern void play_sequence(u8 player, u8 seqId, u16 fadeTimer);
extern u8 sCurrentBackgroundMusicSeqId;
void imageSelect()
{
    u8* ramPtr = (u8 *)0x80026000;
    u32 width = 192;
    u32 height = 128;

    _start[1] = 0;
    if (gMarioState->numStars < 30)
    {
        if (SELECT_STAR == gState)
        {
            gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
            render_star_select();
            if (gCurrCourseNum == 0)
                render_course_select();

            gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

            if (gPlayer3Controller->buttonPressed & B_BUTTON)
            {
                load_image();
                gState = SHOW_IMAGE;
            }
        }
        else if (SHOW_IMAGE == gState)
        {
            gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
            switch_star_lr();
            int_to_str(gSelectedStar + 1, uHintArtNumber + 9);
            if (has_star(gSelectedStar))
            {
                gDPSetEnvColor(gDisplayListHead++, 100, 255, 100, gDialogTextAlpha);
            }
            else
            {
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
            }
            print_generic_string_centered_aligned(uHintArtNumber, 212);

            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
            print_generic_string_centered_aligned(uPressBToHideTheHint, 15);
            print_generic_string(13, 120, uLeft);
            print_generic_string(300, 120, uRight);
            gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
            render_multi_image(ramPtr, (320 - width) / 2, (240 - height) / 2, width * 2, height * 2, 1, 1, G_CYC_1CYCLE);
            _start[1] = 1;

            if (gPlayer3Controller->buttonPressed & B_BUTTON)
            {
                gState = SELECT_STAR;
            }
        }
    }
    else
    {
        if (sCurrentBackgroundMusicSeqId != 0x1a)
            play_sequence(0, 0x1a, 0);

        if (gSelectedStar != 30)
        {
            gSelectedStar = 30;
            load_image();
        }

        static const u8 sPinkColor[] = { 0xd6, 0x00, 0x73 };
        static const u8 sPurpleColor[] = { 0x00, 0x89, 0xff };
        f32 colorOff = (1.f + sins(gGlobalTimer * 545)) / 2.f;
        u8 currentColor[] = {
            (sPinkColor[0] * colorOff + sPurpleColor[0] * (1.f - colorOff)),
            (sPinkColor[1] * colorOff + sPurpleColor[1] * (1.f - colorOff)),
            (sPinkColor[2] * colorOff + sPurpleColor[2] * (1.f - colorOff)),
        };
        gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
        gDPSetEnvColor(gDisplayListHead++, currentColor[0], currentColor[1], currentColor[2], gDialogTextAlpha);
        print_generic_string_centered_aligned(uThanksForPLaying, 212);
        print_generic_string_centered_aligned(uMadeBy, 15);
        gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
        render_multi_image(ramPtr, (320 - width) / 2, (240 - height) / 2, width * 2, height * 2, 1, 1, G_CYC_1CYCLE);
        _start[1] = 1;
    }
}
