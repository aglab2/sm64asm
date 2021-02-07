#include "boo_key.h"
#include "key.h"
#include "bookshelf.h"
#include "book.h"
#include "locked_box.h"
#include "wall_translucer.h"
#include "mips.h"
#include "mips_ctl.h"
#include "cits_rotat.h"
#include "particle_spawner.h"
#include "two_d.h"
#include "beach_2d_ctl.h"
#include "rooms_coll.h"
#include "red_indicator.h"
#include "hud_relocator.h"
#include "c1_moving.h"
#include "c1_upwards.h"
#include "c2_cannon.h"
#include "c5_flying.h"
#include "b1_fight_ctl.h"
#include "c8_deathfloor.h"
#include "c9_puzzle.h"
#include "c9_puzzle_coin.h"
#include "ow_rock.h"
#include "cw_death.h"
#include "c7_timer.h"
#include "funny_text.h"
#include "b3f_ctl.h"
#include "b3f_platform.h"
#include "b3f_switch.h"
#include "b3f_fireball.h"
#include "credits.h"
#include "c9_door.h"
#include "dorrie_ctl.h"
#include "invi_wall_fixer.h"
#include "cw_scroll.h"
#include "cheeze_checkpoint.h"
#include "cheeze_zap.h"

#define REGISTER_BEHAVIOR(list, obj) list, 0x04000000, (int) obj::Behavior,

int _start[] = {
    REGISTER_BEHAVIOR(0x00090000, BookShelf)      // 408000
    REGISTER_BEHAVIOR(0x00090000, LockedBox)      // 40800C
    REGISTER_BEHAVIOR(0x00060000, Key)            // 408018
    REGISTER_BEHAVIOR(0x00040000, BooKey)         // 408024
    REGISTER_BEHAVIOR(0x00040000, Book)           // 408030
    REGISTER_BEHAVIOR(0x00040000, WallTranslucer) // 40803C
    REGISTER_BEHAVIOR(0x00040000, MIPS)           // 408048
    REGISTER_BEHAVIOR(0x00040000, MIPSCtl)        // 408054
    REGISTER_BEHAVIOR(0x00090000, CITSRotat1)     // 408060
    REGISTER_BEHAVIOR(0x00090000, CITSRotat2)     // 40806C
    REGISTER_BEHAVIOR(0x00090000, ParticleSpawner) // 408078
    REGISTER_BEHAVIOR(0x00040000, TwoD)           // 408084
    REGISTER_BEHAVIOR(0x00040000, BeachTwoDCtl)   // 408090
    REGISTER_BEHAVIOR(0x00040000, RoomsColl)      // 40809C
    REGISTER_BEHAVIOR(0x00040000, RedIndicator)   // 4080A8
    REGISTER_BEHAVIOR(0x00040000, HUDRelocator)   // 4080B4
    REGISTER_BEHAVIOR(0x00090000, C1Moving)       // 4080C0
    REGISTER_BEHAVIOR(0x00090000, C1Upwards)      // 4080CC
    REGISTER_BEHAVIOR(0x00040000, C2Cannon)       // 4080D8
    REGISTER_BEHAVIOR(0x00040000, C5Flying)       // 4080E4
    REGISTER_BEHAVIOR(0x00040000, B1FightCtl)     // 4080F0
    REGISTER_BEHAVIOR(0x00090000, C8DeathFloor)   // 4080FC
    REGISTER_BEHAVIOR(0x00090000, C9Puzzle)       // 408108
    REGISTER_BEHAVIOR(0x00060000, C9PuzzleCoin)   // 408114
    REGISTER_BEHAVIOR(0x00090000, OWRock)         // 408120
    REGISTER_BEHAVIOR(0x00040000, CWDeath)        // 40812C
    REGISTER_BEHAVIOR(0x00040000, C7Timer)        // 408138
    REGISTER_BEHAVIOR(0x00040000, FunnyText)      // 408144
    REGISTER_BEHAVIOR(0x00090000, B3FPlatform)    // 408150
    REGISTER_BEHAVIOR(0x00040000, B3FCtl)         // 40815c
    REGISTER_BEHAVIOR(0x00090000, B3FSwitch)      // 408168
    REGISTER_BEHAVIOR(0x00060000, B3FFireball)    // 408174
    REGISTER_BEHAVIOR(0x00040000, Credits)        // 408180
    REGISTER_BEHAVIOR(0x00090000, C9Door)         // 40818C
    REGISTER_BEHAVIOR(0x00040000, DorrieCtl)      // 408198
    REGISTER_BEHAVIOR(0x00040000, InviWallFixer)  // 4081A4
    REGISTER_BEHAVIOR(0x00040000, CWScroll)       // 4081B0
    REGISTER_BEHAVIOR(0x00040000, CheezeCheckPoint) // 4081BC
    REGISTER_BEHAVIOR(0x00040000, BeachTwoDRevert) // 4081C8
    REGISTER_BEHAVIOR(0x00090000, CheezeZap)      // 4081D4
};