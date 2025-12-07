#include "types.h"

#include "image_select.h"
#include "gp_box.h"
#include "levels.h"

#include "game/area.h"
#include "game/interaction.h"
#include "game/object_helpers.h"
#include "game/print.h"
#include "game/mario.h"
#include "game/sound_init.h"
#include "engine/behavior_script.h"
#include "sm64.h"

extern void *alloc_display_list(u32 size);
extern u32 gGlobalTimer;

#define REGISTER_BEHAVIOR(list, beh) list, 0x04000000, ((int) beh) - 0x80000000

static void onPause()
{
    imageSelect();
}

// TODO: Remove this trash
// 0x02014470 - 0x020144B0
static const Mtx matrix_identity = {
#ifndef GBI_FLOATS
    {{0x00010000, 0x00000000,
      0x00000001, 0x00000000},
     {0x00000000, 0x00010000,
      0x00000000, 0x00000001},
     {0x00000000, 0x00000000,
      0x00000000, 0x00000000},
     {0x00000000, 0x00000000,
      0x00000000, 0x00000000}}
#else
    {{1.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 1.0f}}
#endif
};


// 0x020144B0 - 0x020144F0
static const Mtx matrix_fullscreen = {
#ifndef GBI_FLOATS
    {{0x00000000, 0x00000000,
      0x00000000, 0x00000000},
     {0x00000000, 0xffff0000,
      0xffffffff, 0xffff0001},
     {((65536 * 2 / SCREEN_WIDTH) << 16) | 0, 0x00000000,
      (0 << 16) | (65536 * 2 / SCREEN_HEIGHT), 0x00000000},
     {0x00000000, 0x00000000,
      0x00000000, 0x00000000}}
#else
    {{2.0f / SCREEN_WIDTH, 0.0f, 0.0f, 0.0f},
    {0.0f, 2.0f / SCREEN_HEIGHT, 0.0f, 0.0f},
    {0.0f, 0.0f, -1.0f, 0.0f},
    {-1.0f, -1.0f, -1.0f, 1.0f}}
#endif
};

static const Gfx dl_proj_mtx_fullscreen[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPMatrix(&matrix_identity, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH),
    gsSPMatrix(&matrix_fullscreen, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH),
    gsSPMatrix(&matrix_identity, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH),
    gsSPPerspNormalize(0xFFFF),
    gsSPEndDisplayList(),
};

static int sTitleScreenAlpha = 0;
static Gfx* onTitleScreen(s32 state, struct GraphNode *node, void *context)
{
    Gfx* dl = NULL;
    if (state != 1)
    {
        sTitleScreenAlpha = 0;
    }
    else
    {
        node->flags = (node->flags & 0xFF) | (5 << 8);
        dl = alloc_display_list(5 * sizeof(*dl));
        gSPEndDisplayList(dl);
        gSPEndDisplayList(dl + 1);
        gSPEndDisplayList(dl + 2);
        gSPEndDisplayList(dl + 3);
        gSPEndDisplayList(dl + 4);

        if (gGlobalTimer >= 19) {
            sTitleScreenAlpha += 26;
            if (sTitleScreenAlpha > 255) {
                sTitleScreenAlpha = 255;
            }
        }

        Gfx* dlIter = dl;
        gSPDisplayList(dlIter++, dl_proj_mtx_fullscreen);
        gDPSetRenderMode(dlIter++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
        titleDraw(dlIter, sTitleScreenAlpha);
    }
    return dl;
}

static s8 sShowHintProgress = 0;
static s32 onWaterCancels(struct MarioState *m)
{
    if (m->pos[1] > m->waterLevel - 80) {
        if (m->waterLevel - 80 > m->floorHeight) {
            m->pos[1] = m->waterLevel - 80;
        } else {
            //! If you press B to throw the shell, there is a ~5 frame window
            // where your held object is the shell, but you are not in the
            // water shell swimming action. This allows you to hold the water
            // shell on land (used for cloning in DDD).
            if (m->action == ACT_WATER_SHELL_SWIMMING && m->heldObj != NULL) {
                m->heldObj->oInteractStatus = INT_STATUS_STOP_RIDING;
                m->heldObj = NULL;
                stop_shell_music();
            }

            return transition_submerged_to_walking(m);
        }
    }

    if (m->health < 0x100 && !(m->action & (ACT_FLAG_INTANGIBLE | ACT_FLAG_INVULNERABLE))) {
        set_mario_action(m, ACT_DROWNING, 0);
    }

    if (-1 != sShowHintProgress)
    {
        if (sShowHintProgress < 30)
            sShowHintProgress++;

        print_text_centered(160, sShowHintProgress, "TRY TO GROUNDPOUND");
    }

    if (m->health >= 0x100 && m->input & INPUT_Z_PRESSED) {
        sShowHintProgress = -1;
        set_mario_action(m, ACT_GROUND_POUND, 0);
    }

    return FALSE;
}

static u8 sGpTimer = 0;

s32 onAirborneCancels(struct MarioState *m) {
    if (gCurrCourseNum == 0x16 && !m->heldObj)
    {
        f32 d;
        struct Object* chuckya = obj_find_nearest_object_with_behavior((const BehaviorScript*) 0x13000528, &d);
        if (chuckya)
        {
            if (0 == (chuckya->oTimer % 16))
            {
                struct Object* sparkle = spawn_object(chuckya, MODEL_SPARKLES, (const BehaviorScript*) 0x13000a14);
                sparkle->oPosX = chuckya->oPosX + (RandomFloat() * 200.0f) - 100.0f;
                sparkle->oPosY = chuckya->oPosY + 100.0f;
                sparkle->oPosZ = chuckya->oPosZ + (RandomFloat() * 200.0f) - 100.0f;
            }
        }
    }

    if (m->action == ACT_GROUND_POUND)
    {
        if (m->actionTimer < 10)
        {
            sGpTimer = 0;
        }
        else
        {
            sGpTimer++;
        }

        if (sGpTimer < 15)
        {
            return FALSE;
        }
    }

    if (m->pos[1] < m->waterLevel - 100) {
        return set_water_plunge_action(m);
    }

    if (m->input & INPUT_SQUISHED) {
        return drop_and_set_mario_action(m, ACT_SQUISHED, 0);
    }

    if (m->floor->type == SURFACE_VERTICAL_WIND && (m->action & ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION)) {
        return drop_and_set_mario_action(m, ACT_VERTICAL_WIND, 0);
    }

    m->quicksandDepth = 0.0f;
    return FALSE;
}

s32 isHeavy(struct MarioState* m)
{
    if (gCurrCourseNum == 0x16)
        return 0;

    return m->heldObj->oInteractionSubtype & INT_SUBTYPE_GRABS_MARIO;
}

uintptr_t _start[] __attribute__((section(".data._start"))) = {
    (uintptr_t) onPause, 
    0, // pause blocked
    REGISTER_BEHAVIOR(0x00060000, gpBoxBehavior),
    (uintptr_t) onTitleScreen, 
    (uintptr_t) onWaterCancels,
    (uintptr_t) onAirborneCancels,
    (uintptr_t) isHeavy,
};
