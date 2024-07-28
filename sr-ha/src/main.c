#include "types.h"

#include "image_select.h"
#include "gp_box.h"
#include "levels.h"

#include "game/area.h"
#include "game/interaction.h"
#include "game/print.h"
#include "game/mario.h"
#include "game/sound_init.h"
#include "sm64.h"

extern void *alloc_display_list(u32 size);

#define REGISTER_BEHAVIOR(list, beh) list, 0x04000000, ((int) beh) - 0x80000000

static void onPause()
{
    imageSelect();
}

static Gfx* onTitleScreen(s32 state, struct GraphNode *node, void *context)
{
    Gfx* dl = NULL;
    if (state != 1)
    {
    }
    else
    {
        node->flags = (node->flags & 0xFF) | (1 << 8);
        dl = alloc_display_list(5 * sizeof(*dl));
        gSPEndDisplayList(dl);
        gSPEndDisplayList(dl + 1);
        gSPEndDisplayList(dl + 2);
        gSPEndDisplayList(dl + 3);
        gSPEndDisplayList(dl + 4);

        Gfx* dlIter = dl;
        gDPSetRenderMode(dlIter++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
        titleDraw(dlIter, 0xa0);
    }
    return dl;
}

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

    if (m->health >= 0x100 && m->input & INPUT_Z_PRESSED) {
        set_mario_action(m, ACT_GROUND_POUND, 0);
    }

    return FALSE;
}

static u8 sGpTimer = 0;

s32 onAirborneCancels(struct MarioState *m) {
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

        if (sGpTimer < 10)
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
    if (gCurrCourseNum == LevelConv_SM64Levels_VC)
        return 0;

    return m->heldObj->oInteractionSubtype & INT_SUBTYPE_GRABS_MARIO;
}

uintptr_t _start[] = {
    (uintptr_t) onPause, 
    0, // pause blocked
    REGISTER_BEHAVIOR(0x00060000, gpBoxBehavior),
    (uintptr_t) onTitleScreen, 
    (uintptr_t) onWaterCancels,
    (uintptr_t) onAirborneCancels,
    (uintptr_t) isHeavy,
};
