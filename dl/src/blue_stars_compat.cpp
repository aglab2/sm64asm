#include "blue_stars_compat.h"
#include <sm64.h>
extern "C"
{
    #include <game/ingame_menu.h>
    #include <game/game.h>
    #include <game/level_update.h>
    #include <game/mario.h>
    #include <game/object_helpers.h>
    #include <game/object_list_processor.h>
    #include <game/print.h>
    #include <game/save_file.h>
    #include <PR/gbi.h>
    extern void print_hud_course_complete_coins(s16 x, s16 y);
    extern void play_star_fanfare_and_flash_hud(s32 arg, u8 starNum);
    extern s32 _save_file_get_total_star_count(s32 fileIndex, s32 minCourse, s32 maxCourse);
}
#include "object_fields.h"

u32 setMarioActionOnStarGrab(struct MarioState *m, u32 action, u32 actionArg)
{
	u32 bparam = m->usedObj->oBehParams;
    if (bparam & 0xff) // bparam4
    {
        action = ACT_STAR_DANCE_WATER;
    }

    return set_mario_action(m, action, actionArg);
}

s16 setDoorStarCount(struct MarioState *m, UNUSED u32 interactType, struct Object *o)
{
    s16 requiredNumStars = o->OBJECT_FIELD_U32(0x40) >> 24;
    return requiredNumStars;
}

s16 setDoorStarCurrent(struct Object *o, int from, int to)
{
    s16 bparam4 = o->OBJECT_FIELD_U32(0x40) & 0xff;
    int file = bparam4 ? 0x100 : 0;
    return _save_file_get_total_star_count(file | (gCurrSaveFileNum - 1), from, to);
}

u32 getTextBoxForStarCount(s16 requiredNumStars, struct Object *o)
{
    s16 bparam4 = o->OBJECT_FIELD_U32(0x40) & 0xff;
    bool blueStarDoor = 0 != bparam4;

    u8 textBox = 0x16;
    if (blueStarDoor)
    {
        textBox = 0x81;
    }
    else
    {
        switch (requiredNumStars)
        {
        case 1:
            textBox = 0x01;
            break;
        case 3:
            textBox = 0x0a;
            break;
        case 8:
            textBox = 0x5E;
            break;
        case 30:
            textBox = 0x8E;
            break;
        case 50:
            textBox = 0x90;
            break;
        case 70:
            textBox = 0xC8;
            break;
        default:
            break;
        }
    }

    return textBox << 16;
}

void afterStarInit()
{
    int bparam4 = gCurrentObject->oBehParams & 0xff;
    if (!bparam4)
        return;

    s16* requiredStarsArr = (s16*) 0x804051e0;
    s16 requiredStars = requiredStarsArr[bparam4 - 1];
    if (gMarioStates->numStars < requiredStars)
    {
        gCurrentObject->activeFlags = 0;
        return;
    }
    
    s8 starId = (gCurrentObject->oBehParams >> 24) & 0xFF;
    u8 currentLevelStarFlags = save_file_get_star_flags(0x100 | (gCurrSaveFileNum - 1), gCurrCourseNum - 1);

    if (currentLevelStarFlags & (1 << starId)) {
        gCurrentObject->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_TRANSPARENT_STAR];
    } else {
        gCurrentObject->header.gfx.sharedChild = gLoadedGraphNodes[0xe2];
    }
}

s32 renderCourseCompleteBlueStar()
{
    if (!(0xff00 & (*(int*) 0x804051d0)))
        return 1;

    // a Blue Star was collected
    static const u8 name[] = { 0x0a, 0x9E, 0x0B, 0x15, 0x1E, 0x0E, 0x9E, 0x1C, 0x1D, 0x0A, 0x1B, 0x9E, 0x20, 0x0A, 0x1C, 0x9E, 0x0C, 0x18, 0x15, 0x15, 0x0E, 0x0C, 0x1D, 0x0E, 0x0D, 0xFF };
    u8 textSymStar[] = { 0x27, (u8) GLYPH_SPACE };
    print_hud_course_complete_coins(118, 103);
    play_star_fanfare_and_flash_hud(1, 1 << (gLastCompletedStarNum - 1));

    gSPDisplayList(gDisplayListHead++, 0x0000000002011b60);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
    print_hud_lut_string(HUD_LUT_GLOBAL, 55, 77, textSymStar);
    gSPDisplayList(gDisplayListHead++, 0x0000000002011bc8);
    gSPDisplayList(gDisplayListHead++, 0x0000000002011cc8);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, gDialogTextAlpha);
    print_generic_string(76, 145, name);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
    print_generic_string(74, 147, name);
    gSPDisplayList(gDisplayListHead++, 0x0000000002011d50);

    return 0;
}
