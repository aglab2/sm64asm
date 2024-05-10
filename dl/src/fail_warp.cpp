#include "fail_warp.h"
#include <sm64.h>
extern "C"
{
    #include <game/area.h>
    #include <game/camera.h>
    #include <game/level_update.h>
    #include <game/mario.h>
    #include <game/memory.h>
    #include <game/print.h>
    #include <game/display.h>
    #include <game/game.h>
    #include <game/ingame_menu.h>
    #include <libc/math.h>
    #include <level_commands.h>
    #include <surface_terrains.h>
    void set_camera_mode_8_directions(struct Camera *c);

    extern s16 s8DirModeYawOffset;
}
#include "object_fields.h"
#include "blue_star_mode.h"

#define SURFACE_IS_INSTANT_WARP(cmd)            (((cmd) >= SURFACE_INSTANT_WARP_1B) && ((cmd) < SURFACE_INSTANT_WARP_1B + INSTANT_WARP_INDEX_STOP))
#define SURFACE_IS_WARP(cmd)                    (((cmd) == SURFACE_LOOK_UP_WARP) || ((cmd) == SURFACE_WOBBLING_WARP) || SURFACE_IS_PAINTING_WARP(cmd) || SURFACE_IS_INSTANT_WARP(cmd))
#define SURFACE_IS_UNSAFE(cmd)                  (((cmd) == SURFACE_BURNING) || SURFACE_IS_QUICKSAND(cmd) || SURFACE_IS_WARP(cmd) || ((cmd) == SURFACE_DEATH_PLANE) || ((cmd) == SURFACE_NOISE_DEFAULT) || ((cmd) == SURFACE_SLIPPERY))

#define WARP_ID_SPOOFED 0xf4

static int sSafePosArea = 0;
static int sSafePosLevel = 0;
static Vec3s sSafePos{};
static s16 sSafePosAngle;
void setSafePos(struct MarioState *m)
{
    // print_text_fmt_int(20, 20, "X %d", (int) m->pos[0]);
    // print_text_fmt_int(20, 40, "Y %d", (int) m->pos[1]);
    // print_text_fmt_int(20, 60, "Z %d", (int) m->pos[2]);
    sSafePos[0] = m->pos[0];
    sSafePos[1] = m->pos[1];
    sSafePos[2] = m->pos[2];
    sSafePosAngle = m->faceAngle[1];
    sSafePosArea = gCurrAreaIndex;
    sSafePosLevel = gCurrLevelNum;
}

void marioSetSafePos(struct MarioState *m, struct Surface *floor)
{
    // print_text(20, 80, "POS CHECK");
    m->floor = floor;
    // print_text_fmt_int(20, 100, "FLOOR %x", ((int) floor) & 0xffffff);
    m->floorHeight = m->pos[1];
    if (!floor)
        return;

    // object generated floors might be unsafe so avoid them
    if (floor->object)
        return;

    if (sSafePosArea != gCurrAreaIndex || sSafePosLevel != gCurrLevelNum) 
    {
        return setSafePos(m);
    }
    
    bool slideTerrain = (m->area->terrainType & TERRAIN_MASK) == TERRAIN_SLIDE;
    if (slideTerrain)
        return;

    s16 type = floor->type;
    if (!SURFACE_IS_UNSAFE(type) && type != SURFACE_VERY_SLIPPERY && floor->normal.y >= 0.8f)
    {
        return setSafePos(m);
    }
}

static struct ObjectWarpNode sSpoofedWarpNode = { };
static struct Object sSpoofedWarpObject = { };
struct ObjectWarpNode* areaGetWarpNode(u8 id)
{
    if (id == WARP_ID_SPOOFED)
    {
        sSpoofedWarpNode.node.id = WARP_ID_SPOOFED;
        sSpoofedWarpNode.node.destLevel = gCurrLevelNum;
        sSpoofedWarpNode.node.destArea = gCurrAreaIndex;
        sSpoofedWarpNode.node.destNode = WARP_ID_SPOOFED;
        sSpoofedWarpNode.object = &sSpoofedWarpObject;
        sSpoofedWarpNode.next = nullptr;
        sSpoofedWarpObject.oPosX = sSafePos[0];
        sSpoofedWarpObject.oPosY = sSafePos[1];
        sSpoofedWarpObject.oPosZ = sSafePos[2];
        sSpoofedWarpObject.oFaceAngleYaw = sSafePosAngle;
        sSpoofedWarpObject.oMoveAngleYaw = sSafePosAngle;
        sSpoofedWarpObject.behavior = (const BehaviorScript*) segmented_to_virtual((const BehaviorScript*) 0x13002f60);
        
        return &sSpoofedWarpNode;
    }
    else
    {
        struct ObjectWarpNode *node;
        for (node = gCurrentArea->warpNodes; node != NULL; node = node->next) {
            if (node->node.id == id) {
                break;
            }
        }

        return node;
    }
}

static void spoofWarp(struct MarioState *m)
{
    m->usedObj = &sSpoofedWarpObject;
    sSpoofedWarpObject.oBehParams = WARP_ID_SPOOFED << 16;
    sSpoofedWarpObject.oBehParams2ndByte = WARP_ID_SPOOFED;
}

void preLevelTriggerWarp(struct MarioState *m, s32* warpOp)
{
    int Damage = 0;
    int NoReturn = 0;
    sDelayedWarpArg = 0;
    sDelayedWarpOp = *warpOp;
    if (*warpOp != WARP_OP_DEATH && *warpOp != WARP_OP_WARP_FLOOR)
    {
        return;
    }

    if ((gCurrLevelNum == LEVEL_COTMC) || (gCurrLevelNum == LEVEL_VCUTM) || (gCurrLevelNum == LEVEL_ENDING))
    {
        Damage = 0x100;
        NoReturn = 0x180;
    }
    else if (blue_star_mode_enabled())
    {
        Damage = 0x200;
        NoReturn = 0x280;
    }
    else
    {
        Damage = 0x400;
        NoReturn = 0x480;
    }

    if (m->health <= NoReturn)
        return;

    m->health = (m->health & (~0xff)) + 0x80;
    if ((m->action == ACT_BURNING_JUMP) || (m->action == ACT_BURNING_FALL) || (m->action == ACT_BURNING_GROUND))
    {
        drop_and_set_mario_action(m, ACT_FREEFALL, 0);
    }

    m->hurtCounter = Damage / 0x40;
    *warpOp = WARP_OP_TELEPORT;
    spoofWarp(m);
}

void initMarioAfterQuickWarp(struct MarioState *m)
{
    set_mario_action(m, ACT_IDLE, 0);
    auto camera = gCurrentArea->camera;
    set_camera_mode_8_directions(camera);
    s8DirModeYawOffset = sSafePosAngle & 0xe000;
    reset_camera(camera);
    
    bool slideTerrain = (m->area->terrainType & TERRAIN_MASK) == TERRAIN_SLIDE;
    if (slideTerrain)
        level_control_timer(TIMER_CONTROL_HIDE);
}

void triggerFailWarp(struct MarioState* m)
{
    spoofWarp(m);
    level_trigger_warp(m, WARP_OP_TELEPORT);
}
