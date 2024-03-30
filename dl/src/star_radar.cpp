#include "types.h"
#include <object_fields.h>

extern "C"
{
    #include "course_table.h"
    #include <game/area.h>
    #include <game/display.h>
    #include <game/game.h>
    #include <game/ingame_menu.h>
    #include <game/level_update.h>
    #include <game/mario.h>
    #include <game/memory.h>
    #include <game/object_helpers.h>
    #include <game/object_list_processor.h>
    #include <game/print.h>
    #include <libc/math.h>
    #include <level_commands.h>
    extern s32 _save_file_get_total_star_count(s32 fileIndex, s32 minCourse, s32 maxCourse);
    extern s32 _save_file_get_star_flags(s32 fileIndex, s32 courseIndex);
    extern s32 save_file_get_flags(void);
    extern void render_hud_tex_lut(s32 x, s32 y, u8 *texture);
    extern f32 _sqrtf(f32 x);
}

#include "blue_star_mode.h"

using Texture = u8;

static struct Object *obj_find_nearest_object_with_behavior_and_bparam1(const BehaviorScript *behavior, int bparam1) {
    uintptr_t *behaviorAddr = (uintptr_t *) segmented_to_virtual(behavior);
    struct ObjectNode *listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    struct Object *obj = (struct Object *) listHead->next;
    while (obj != (struct Object *) listHead) {
        if (obj->behavior == behaviorAddr
            && obj->activeFlags != 0
            && (((obj->oBehParams) >> 24) & 0xff) == bparam1
            && (((obj->oBehParams)) & 0xff)
        ) {
            return obj;
        }

        obj = (struct Object *) obj->header.next;
    }

    return nullptr;
}

static struct Object *obj_find_nearest_object_with_behavior_and_bparam2(const BehaviorScript *behavior, int bparam2) {
    uintptr_t *behaviorAddr = (uintptr_t *) segmented_to_virtual(behavior);
    struct ObjectNode *listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    struct Object *obj = (struct Object *) listHead->next;
    while (obj != (struct Object *) listHead) {
        if (obj->behavior == behaviorAddr
            && obj->activeFlags != 0
            && (((obj->oBehParams) >> 16) & 0xff) == bparam2
        ) {
            return obj;
        }

        obj = (struct Object *) obj->header.next;
    }

    return nullptr;
}

static bool hasAnyWithBparam4(const BehaviorScript *behavior)
{
    uintptr_t *behaviorAddr = (uintptr_t *) segmented_to_virtual(behavior);
    struct ObjectNode *listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    struct Object *obj = (struct Object *) listHead->next;
    while (obj != (struct Object *) listHead) {
        if (obj->behavior == behaviorAddr
            && obj->activeFlags != 0
            && (((obj->oBehParams)) & 0xff)
        ) {
            return true;
        }

        obj = (struct Object *) obj->header.next;
    }

    return false;
}

static int sLastCheckedLevel = 0;
static bool sRenderStarRadar = false;

void renderStarRadar()
{
    if (!gMarioObject)
        return;

    if (sLastCheckedLevel != gCurrLevelNum)
    {
        sRenderStarRadar = hasAnyWithBparam4((BehaviorScript*) 0x0000000013003e3c);
        sLastCheckedLevel = gCurrLevelNum;
    }

    if (!sRenderStarRadar)
        return;

    // print_text_fmt_int(20, 80, "F %d", (int) gMarioState->floorHeight);
    // print_text_fmt_int(20, 60, "X %d", (int) gMarioState->pos[0]);
    // print_text_fmt_int(20, 40, "Y %d", (int) gMarioState->pos[1]);
    // print_text_fmt_int(20, 20, "Z %d", (int) gMarioState->pos[2]);

    static f32 sTimers[8] = { 0 };
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wc99-designator"
    static char sStarMasks[] = {
        [ LEVEL_CASTLE_COURTYARD ] = 0b0,
        [ LEVEL_CASTLE_GROUNDS ]   = 0b1111111,
        [ LEVEL_CASTLE         ]   = 0b0,

        [ LEVEL_BOB ] = (1 << 7) - 1,
        [ LEVEL_WF  ] = (1 << 7) - 1,
        [ LEVEL_JRB ] = (1 << 7) - 1,
        [ LEVEL_CCM ] = (1 << 7) - 1,
        [ LEVEL_BBH ] = (1 << 7) - 1,
        [ LEVEL_HMC ] = (1 << 7) - 1,
        [ LEVEL_LLL ] = (1 << 7) - 1,
        [ LEVEL_SSL ] = (1 << 7) - 1,
        [ LEVEL_DDD ] = (1 << 7) - 1,
        [ LEVEL_SL  ] = (1 << 7) - 1,
        [ LEVEL_WDW ] = (1 << 7) - 1,
        [ LEVEL_TTM ] = (1 << 7) - 1,
        [ LEVEL_THI ] = (1 << 7) - 1,
        [ LEVEL_TTC ] = (1 << 7) - 1,
        [ LEVEL_RR  ] = (1 << 7) - 1,

        [ LEVEL_TOTWC ] = 0b1111111,
        [ LEVEL_COTMC ] = 0b1111111,
        [ LEVEL_WMOTR ] = 0b111111,
        [ LEVEL_VCUTM ] = 0b1111111,
        [ LEVEL_SA    ] = 0b1111111,
        
        [ LEVEL_BITDW ] = 0b11111,
        [ LEVEL_BITFS ] = 0b111111,
        [ LEVEL_BITS  ] = 0b11111,

        [ LEVEL_PSS ] = 0b1111111,
        [ LEVEL_ENDING ] = 0b1111111,
    };
#pragma GCC diagnostic pop

    Texture* grayTexture = (Texture*) 0x04078200;
    Texture* yellowTexture = (Texture*) 0x0407CA00;
    Texture* redTexture = (Texture*) 0x0407EE00;
    Texture* blueTexture = (Texture*) 0x0407A600;

    if (gCurrLevelNum != LEVEL_BOWSER_1 && gCurrLevelNum != LEVEL_BOWSER_2 && gCurrLevelNum != LEVEL_BOWSER_3)
    {
        int starMask = sStarMasks[gCurrLevelNum];
        if (gCurrLevelNum == LEVEL_CASTLE && gCurrAreaIndex == 1)
        {
            starMask = 0;
        }

        if (gCurrLevelNum == LEVEL_CASTLE_GROUNDS && gCurrAreaIndex != 1)
        {
            starMask = 0;
        }

        // F-Zero Slides

        if (((gCurrLevelNum == LEVEL_COTMC) || (gCurrLevelNum == LEVEL_VCUTM) || (gCurrLevelNum == LEVEL_ENDING)) && gCurrAreaIndex == 1)
        {
            starMask = 0b111111;
        }

        if (((gCurrLevelNum == LEVEL_COTMC) || (gCurrLevelNum == LEVEL_VCUTM) || (gCurrLevelNum == LEVEL_ENDING)) && gCurrAreaIndex == 2)
        {
            starMask = 0b1000000;
        }

        if (((gCurrLevelNum == LEVEL_COTMC) || (gCurrLevelNum == LEVEL_VCUTM)) && ((gCurrAreaIndex == 3) || (gCurrAreaIndex == 4)))
        {
            starMask = 0b111111;
        }

        if (gCurrLevelNum == LEVEL_ENDING && gCurrAreaIndex == 3)
        {
            starMask = 0b1111111;
        }
        
        if (gCurrLevelNum == LEVEL_ENDING && gCurrAreaIndex == 4)
        {
            starMask = 0;
        }

        // Switch Level WC Slot

        if (gCurrLevelNum == LEVEL_TOTWC && gCurrAreaIndex == 1)
        {
            starMask = 0b11;
        }

        if (gCurrLevelNum == LEVEL_TOTWC && gCurrAreaIndex == 2)
        {
            starMask = 0b110000;
        }

        if (gCurrLevelNum == LEVEL_TOTWC && gCurrAreaIndex == 3)
        {
            starMask = 0b1100;
        }

        if (gCurrLevelNum == LEVEL_TOTWC && gCurrAreaIndex == 4)
        {
            starMask = 0b1000000;
        }

        // Bowser 2

        if (gCurrLevelNum == LEVEL_BITFS && gCurrAreaIndex == 1)
        {
            starMask = 0b11111;
        }

        if (gCurrLevelNum == LEVEL_BITFS && gCurrAreaIndex == 2)
        {
            starMask = 0b100000;
        }

        // Rest

        if (gCurrLevelNum == LEVEL_CASTLE_COURTYARD && gCurrAreaIndex != 5)
        {
            starMask = 0;
        }

        if (0 == starMask)
        {
            return;
        }

        gSPDisplayList(gDisplayListHead++, 0x02011ac0);
#if 0
        int cnt = 0;
        for (int i = 0; i < 8; i++)
        {
            int bit = 1 << i;
            if (bit & starMask)
                cnt++;
        }
#endif
 
        int collectedMask = _save_file_get_star_flags(0x100 | (gCurrSaveFileNum - 1), gCurrCourseNum - 1);
        int off = 0;
        int canRenderStarRadar = true;
        for (int i = 0; i < 8; i++)
        {
            int bit = 1 << i;
            if (bit & starMask)
            {
                Texture* tex = nullptr;
            
                if (bit & collectedMask)
                {
                    tex = (Texture*) 0x04078000;
                }
                else
                {
                    struct Object* star = obj_find_nearest_object_with_behavior_and_bparam1((BehaviorScript*) 0x0000000013003e3c, i);
                    if (star)
                    {
                        if (canRenderStarRadar)
                        {
                            f32 x = star->oPosX - gMarioObject->oPosX;
                            f32 y = star->oPosY - gMarioObject->oPosY;
                            f32 z = star->oPosZ - gMarioObject->oPosZ;

                            f32 d = _sqrtf(x * x + y * y + z * z * 3.f);
                            if (d < 100.f)
                                d = 100.f;

                            f32 spd = 1200.f / d;
                            sTimers[i] += spd;
                            Texture* startingTexture = grayTexture;

                            if (spd > 0.11f)
                                startingTexture = blueTexture;

                            if (spd > 0.3f)
                                startingTexture = yellowTexture;

                            if (spd > 1.f)
                                startingTexture = redTexture;

                            tex = startingTexture + 0x200 * (((unsigned) sTimers[i]) % 18);
#if 0
                            canRenderStarRadar = false;
#endif
                        }
                    }
                    else
                    {
                        if (canRenderStarRadar)
                        {
                            tex = (Texture*) 0x04077E00;
                        }
                    }
                }
                
                if (tex)
                    render_hud_tex_lut(4, 210 - 16 * off, tex);

                off++;
            }
        }

        gSPDisplayList(gDisplayListHead++, 0x2011b28); 
    }
}

static void renderStars(int stars, int yoff, const char* glyph)
{
    s8 showX = 0;

    if (stars < 100) {
        showX = 1;
    }

    print_text(0x26 - 0x10, yoff, glyph); // 'Star' glyph
    if (showX == 1) {
        print_text(0x26, yoff, "*"); // 'X' glyph
    }
    print_text_fmt_int((showX * 14) + 0x26, yoff, "%d", stars);
}

static void renderBoxRadar()
{
    if (!gMarioObject)
        return;

    s32 flags = save_file_get_flags();
    if (!(flags & 0x000200 /*MOAT*/))
        return;

    Texture* tx = (Texture*) 0x0408f000;
    Texture* t0 = (Texture*) 0x04086400;
    Texture* t1 = (Texture*) 0x04088800;
    Texture* t2 = (Texture*) 0x0408ac00;

    if (blue_star_mode_enabled())
    {
        const s32 targetFlags = 0b111111;
        s32 starFlags0 = _save_file_get_star_flags(0x100 | (gCurrSaveFileNum - 1), COURSE_COTMC - 1);
        s32 starFlags1 = _save_file_get_star_flags(0x100 | (gCurrSaveFileNum - 1), COURSE_VCUTM - 1);
        if ((starFlags0 & targetFlags) == targetFlags && (starFlags1 & targetFlags) == targetFlags)
        {
            return;
        }
    }
    else
    {
        // TODO: It is better to reference course individually
        const s32 targetFlags = 0b111111;
        s32 starFlags0 = _save_file_get_star_flags((gCurrSaveFileNum - 1), COURSE_COTMC - 1);
        s32 starFlags1 = _save_file_get_star_flags((gCurrSaveFileNum - 1), COURSE_VCUTM - 1);
        if ((starFlags0 & targetFlags) == targetFlags && (starFlags1 & targetFlags) == targetFlags)
        {
            return;
        }
    }

    struct Object* box = obj_find_nearest_object_with_behavior_and_bparam2((BehaviorScript*) 0x13002250, 3);
    if (!box)
        return;

    static f32 sTimer = 0;
    
    gSPDisplayList(gDisplayListHead++, 0x02011ac0);
    f32 x = box->oPosX - gMarioObject->oPosX;
    f32 y = box->oPosY - gMarioObject->oPosY;
    f32 z = box->oPosZ - gMarioObject->oPosZ;

    f32 d = _sqrtf(x * x + y * y + z * z * 3.f);
    if (d < 100.f)
        d = 100.f;

    f32 spd = 1800.f / d;
    sTimer += (spd / 2.f);
    Texture* startingTexture = tx;

    if (spd > 0.11f)
        startingTexture = t0;

    if (spd > 0.23f)
        startingTexture = t1;

    if (spd > 0.5f)
        startingTexture = t2;

    Texture* tex = startingTexture + 0x200 * (((unsigned) sTimer) % 18);
    render_hud_tex_lut(5, 15, tex);

    gSPDisplayList(gDisplayListHead++, 0x2011b28); 
}

extern u8 sCurrentBackgroundMusicSeqId;
extern int gLoopCount;
extern int gMusicOverridePrint;
extern int gPC;
void renderHud(s32 renderCoins)
{
    gHudDisplay.stars = _save_file_get_total_star_count(gCurrSaveFileNum - 1, 0, 24);
    s32 blueStarsCount = _save_file_get_total_star_count(0x100 | (gCurrSaveFileNum - 1), 0, 24);
    if (renderCoins)
    {
        int yoff = blueStarsCount ? 20 : 0;
        print_text(0x16, -yoff + 0xbd, "+"); // 'Coin' glyph
        print_text(0x26, -yoff + 0xbd, "*"); // 'X' glyph
        print_text_fmt_int(0x36, -yoff + 0xbd, "%d", gHudDisplay.coins);
    }

    // renders the radar in bottom left corner, not render when all stars are collected because it is pointless
    if (gMarioStates->numStars < 333)
        renderStarRadar();

    renderBoxRadar();

    if (gHudFlash == 1 && gGlobalTimer & 8) {
        return;
    }

    renderStars(gHudDisplay.stars, 0xd1, "-");
    if (blueStarsCount)
    {
        static const char blueStarPrint[] = { 0x17, 0x00 };
        renderStars(blueStarsCount, 0xd1 - 20, blueStarPrint);
    }

#if 0
    static const char kSections[] = { 0x2, 0x7, 0xc };
    print_text_fmt_int(20, 20, "M %d", sCurrentBackgroundMusicSeqId);
    print_text_fmt_int(20, 40, "A %d", gCurrAreaIndex);
    print_text_fmt_int(20, 60, "W %d", kSections[(gCurrAreaIndex - 1) / 2]);
    print_text_fmt_int(20, 80, "L %d", gLoopCount);
    print_text_fmt_int(20, 100, "O %d", gMusicOverridePrint);
    print_text_fmt_int(20, 120, "PC %x", gPC);
#endif
}
