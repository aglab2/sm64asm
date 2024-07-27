#include "types.h"

#include "image_select.h"
#include "gp_box.h"

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

uintptr_t _start[] = {
    (uintptr_t) onPause, 
    0, // pause blocked
    REGISTER_BEHAVIOR(0x00060000, gpBoxBehavior),
    (uintptr_t) onTitleScreen, 
};
