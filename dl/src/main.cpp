#include "types.h"
#include <sm64.h>
extern "C"
{
    #include <course_table.h>
    #include <level_table.h>
    #include <game/area.h>
    extern void initiate_warp(s16 destLevel, s16 destArea, s16 destWarpNode, s32 arg3);
}
#include "act_select.h"
#include "blue_star_block.h"
#include "blue_stars_compat.h"
#include "bully_lava_death.h"
#include "change_music.h"
#include "ex_objects.h"
#include "fail_warp.h"
#include "green_sb_resetter.h"
#include "endscreen_blocker.h"
#include "sound_farewell.h"
#include "star_radar.h"
#include "stardisplay.h"
#include "omm.h"
#include "wall_cucking.h"
#include "whomp_king.h"

#define REGISTER_BEHAVIOR(list, obj) list, 0x04000000, (uintptr_t) VIRTUAL_TO_PHYSICAL2(obj::Behavior)

// exit course warp
static s16 selectWarp(s32 type)
{
    if (type == 3)
    {
        initiate_warp(LEVEL_CASTLE, 1, 0xA, 0);
        return COURSE_NONE;
    }
    else
    {
        auto onode = area_get_warp_node(gCurrCourseNum == COURSE_WMOTR ? 0x1 : 0xf1);
        auto& node = onode->node;
        initiate_warp(node.destLevel, node.destArea, node.destNode, 0);
        return COURSE_NONE;
    }
}

static const uintptr_t kGeoLayouts[] = 
{
    0x220800E2, (uintptr_t) VIRTUAL_TO_PHYSICAL2(star_geo), // new blue star
    0x210800E4, 0x4085FE0, // blue star block model
    0x07040000
};

// 0x3FD0000
uintptr_t _start[] =
{
    (uintptr_t) setMarioActionOnStarGrab,            // 801ce000 : 0
    (uintptr_t) setDoorStarCount,                    // 801ce004 : 1
    REGISTER_BEHAVIOR(0x00040000, EndscreenBlocker), // 801ce008 : 2
    (uintptr_t) getTextBoxForStarCount,              // 801ce014 : 5
    (uintptr_t) afterStarInit,                       // 801ce018 : 6
    (uintptr_t) renderHud,                           // 801ce01c : 7
    0x06080000, (uintptr_t) VIRTUAL_TO_PHYSICAL2(kGeoLayouts), 0x07040000, // 801ce020 : 8
    (uintptr_t) setDoorStarCurrent,                  // 801ce02c : 11
    (uintptr_t) renderCourseCompleteBlueStar,        // 801ce030 : 12
    (uintptr_t) marioSetSafePos,                     // 801ce034 : 13
    (uintptr_t) areaGetWarpNode,                     // 801ce038 : 14
    (uintptr_t) preLevelTriggerWarp,                 // 801ce03c : 15
    REGISTER_BEHAVIOR(0x00040000, ChangeMusic),      // 801ce040 : 16
    (uintptr_t) preGreenSwitchBoard,                 // 801ce04C : 19
    REGISTER_BEHAVIOR(0x00090000, GreenSwitchBlockResetter), // 801ce050 : 20
    (uintptr_t) prePlayTransition,                   // 801ce05c : 23
    (uintptr_t) pickBgColor,                         // 801ce060 : 24
    REGISTER_BEHAVIOR(0x00090000, BlueStarBlock),    // 801ce064 : 25
    (uintptr_t) clearObjects,                        // 801ce070 : 28
    (uintptr_t) initFreeObjectList,                  // 801ce074 : 29
    (uintptr_t) actSelectPath,                       // 801ce078 : 30
    (uintptr_t) selectWarp,                          // 801ce07c : 31
    (uintptr_t) initMarioAfterQuickWarp,             // 801ce080 : 32
    (uintptr_t) StarDisplay,                         // 801ce084 : 33
    (uintptr_t) getBestWall,                         // 801ce088 : 34
    REGISTER_BEHAVIOR(0x00090000, WhompKing),        // 801ce08c : 35
    (uintptr_t) soundPreJmp,                         // 801ce098 : 38
    (uintptr_t) soundPostSequence,                   // 801ce09c : 39
    (uintptr_t) starNoExitSelect,                    // 801ce0a0 : 40
    (uintptr_t) starAfterStarDanceNonStop,           // 801ce0a4 : 41
    (uintptr_t) objLavaDeathBullyThreeBullies,       // 801ce0a8 : 42
    (uintptr_t) objLavaDeathBullySingleBully,        // 801ce0ac : 43
    REGISTER_BEHAVIOR(0x00090000, ResetDeathFlags),  // 801ce0b0 : 44
    (uintptr_t) preStarSpawnInit,                    // 801ce0bc : 47
    (uintptr_t) redCoinStarSpawnInit,                // 801ce0c0 : 48
    (uintptr_t) spawnDialogBoxForNonStopStar,        // 801ce0c4 : 49
};
