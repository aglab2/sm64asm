#include "act_select.h"
extern "C"
{
    #include <game/area.h>
    #include <game/level_update.h>
}

#define	GPACK_RGBA5551(r, g, b, a)	((((r)<<8) & 0xf800) | 		\
					 (((g)<<3) & 0x7c0) |		\
					 (((b)>>2) & 0x3e) | ((a) & 0x1))

#define BG_BEFORE_R (0x10)
#define BG_BEFORE_G (0x10)
#define BG_BEFORE_B (0x10)

#define BG_AFTER_R (0x0)
#define BG_AFTER_G (0x16 / 2)
#define BG_AFTER_B (0x40 / 2)

void prePlayTransition(s16 transType, u8* red, u8* green, u8* blue)
{
    gWarpTransition.isActive = TRUE;
    gWarpTransition.type = transType;
    if (gMarioState->numStars < 150)
    {
        *red = BG_BEFORE_R;
        *green = BG_BEFORE_G;
        *blue = BG_BEFORE_B;
    }
    else
    {
        *red = BG_AFTER_R;
        *green = BG_AFTER_G;
        *blue = BG_AFTER_B;
    }
}

void pickBgColor(Gfx* gfx, u16 color)
{
    if (color == 0xffff)
    {
        color = GPACK_RGBA5551(BG_BEFORE_R, BG_BEFORE_G, BG_BEFORE_B, 1);
    }
    gDPSetFillColor(gfx++, color);
}

// show or hide star select
s32 actSelectPath()
{
    if (gMarioStates->numStars >= 333)
    {
        return 1;
    }

    if (gMarioStates->numStars < 150)
    {
        return 1;
    }
    else
    {
        gCurrActNum = 6;
        return 0;
    }
}
