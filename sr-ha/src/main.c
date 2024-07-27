#include "types.h"

#include "image_select.h"
#include "gp_box.h"

#define REGISTER_BEHAVIOR(list, beh) list, 0x04000000, ((int) beh) - 0x80000000

static void onPause()
{
    imageSelect();
}

static void onTitleScreen(Gfx* gfx, int progress)
{
    titleDraw(gfx, progress);
}

uintptr_t _start[] = {
    (uintptr_t) onPause, 
    0, // pause blocked
    REGISTER_BEHAVIOR(0x00060000, gpBoxBehavior),
    (uintptr_t) onTitleScreen, 
};
