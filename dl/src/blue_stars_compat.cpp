#include "blue_stars_compat.h"
#include "blue_star_mode.h"
#include "fail_warp.h"
#include <sm64.h>
extern "C"
{
    #include <level_commands.h>
    #include <game/area.h>
    #include <game/interaction.h>
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
    extern u8 sCurrentBackgroundMusicSeqId;
    extern void seq_player_play_sequence(u8 player, u8 seqId, u16 arg2);
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
    s32 flags = save_file_get_flags();
    s16 bparam4 = o->OBJECT_FIELD_U32(0x40) & 0xff;
    bool blueStarDoor = 0 != bparam4;

    u8 textBox = 0x16;
    if (blueStarDoor)
    {
        switch (requiredNumStars)
        {
        case 1:
            textBox = 0x81;
            break;
        case 161:
            if(gMarioStates->numStars < 150)
            {
                textBox = 0x81;
                break;
            }
            else
            {
                textBox = 0x7D;
                break;
            }
        case 169:
            textBox = 0x82;
            break;
        case 175:
            textBox = 0xA7;
            break;
        case 176:
            textBox = 0xA3;
            break;
        default:
            break;
        }
    }
    else
    {
        if ((gMarioStates->numStars == 0) && ((flags & (0x000010 | 0x000040)) || (flags & (0x000020 | 0x000080)) || (flags & 0x000200)))
        {
            textBox = 0x08;
        }
        else
        {
        switch (requiredNumStars)
        {
        case 1:
            textBox = 0x18;
            break;
        case 3:
            textBox = 0x19;
            break;
        case 5:
            textBox = 0x19;
            break;
        case 10:
            if (gMarioStates->numStars == 0)
            {
                textBox = 0x08;
                break;
            }
            else
            {
                textBox = 0x19;
                break;
            }
        case 12:
            textBox = 0x19;
            break;
        case 30:
            textBox = 0x19;
            break;
        case 35:
            textBox = 0x19;
            break;
        case 50:
            textBox = 0x19;
            break;
        case 60:
            textBox = 0x19;
            break;
        case 70:
            textBox = 0x19;
            break;
        case 80:
            textBox = 0x19;
            break;
        case 94:
            textBox = 0x19;
            break;
        case 142:
            textBox = 0x1a;
            break;
        case 144:
            textBox = 0x1c;
            break;
        case 145:
            textBox = 0x1b;
            break;
        case 146:
            textBox = 0x1b;
            break;
        case 147:
            textBox = 0x1b;
            break;
        case 148:
            textBox = 0x1b;
            break; 
        case 149:
            textBox = 0x1b;
            break;
        case 200:
            textBox = 0x1d;
            break;
        default:
            break;
        }
        }
    }
    return textBox << 16;
}

void afterStarInit()
{
    int bparam4 = gCurrentObject->oBehParams & 0xff;
    if (!bparam4)
        return;
    
    if (!blue_star_mode_enabled())
    {
        gCurrentObject->activeFlags = 0;
        return;
    }

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

    if (gCurrCourseNum == COURSE_WMOTR && gCurrAreaIndex == 1 && sCurrentBackgroundMusicSeqId != 0xc)
    {
        seq_player_play_sequence(0, 0xc, 0);
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

enum class NonStopState
{
    REGULAR,
    WARP_TO_SAFE_POS,
};
static NonStopState gNonStopState = NonStopState::REGULAR;

s32 starNoExitSelect(struct MarioState *m, u32 interactType, struct Object *o)
{
    // returns noExit variable
    gNonStopState = NonStopState::REGULAR;

    // If it is explicitly marked as a nonstop, return noExit=true
    if (o->oInteractionSubtype & INT_SUBTYPE_NO_EXIT)
    {
        m->health = 0x880;
        return 1;
    }

    s16 bparam4 = o->OBJECT_FIELD_U32(0x40) & 0xff;
    bool blueStar = 0 != bparam4;

    if (!blueStar) // all yellow stars
    {
        if ((gCurrLevelNum == LEVEL_WMOTR && gCurrAreaIndex < 6) || (gCurrLevelNum == LEVEL_CASTLE_COURTYARD && gCurrAreaIndex == 3))
        {
            m->health = 0x880;
            return 1;
        }  
        else
            return 0;
    }

    if ((gCurrLevelNum == LEVEL_COTMC) || (gCurrLevelNum == LEVEL_VCUTM) || (gCurrLevelNum == LEVEL_ENDING && gCurrAreaIndex == 1)
    || (gCurrLevelNum == LEVEL_WMOTR)
    || (gCurrLevelNum == LEVEL_WF  && gCurrAreaIndex == 3)
    || (gCurrLevelNum == LEVEL_LLL  && gCurrAreaIndex == 2)
    || (gCurrLevelNum == LEVEL_SSL  && gCurrAreaIndex == 4)
    || (gCurrLevelNum == LEVEL_SL  && gCurrAreaIndex == 3)
    || (gCurrLevelNum == LEVEL_TTC  && gCurrAreaIndex == 2)
    || (gCurrLevelNum == LEVEL_TOTWC))
        return 0;
    
    if ((gCurrLevelNum == LEVEL_BITFS && gCurrAreaIndex == 2)
    || (gMarioStates->flags & MARIO_WING_CAP)) 
    {
        m->health = 0x880;
        return 1; 
    }

    m->health = 0x880;
    gNonStopState = NonStopState::WARP_TO_SAFE_POS;
    return 1; // no exit==true
}

void starAfterStarDanceNonStop(struct MarioState *m, s32 isInWater)
{
    if (gNonStopState == NonStopState::REGULAR)
    {
        set_mario_action(m, isInWater ? ACT_WATER_IDLE : ACT_IDLE, 0);
    }
    else
    {
        triggerFailWarp(m);
    }
}
