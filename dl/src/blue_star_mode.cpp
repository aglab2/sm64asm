#include "blue_star_mode.h"

extern "C"
{
    #include <game/area.h>
    #include <game/level_update.h>
}

bool sBlueStarModeDisabled = false;

bool blue_star_mode_enabled()
{
    int numStars = gMarioState->numStars;
    if (numStars < 333)
    {
        return numStars >= 150;
    }
    else
    {
        return !sBlueStarModeDisabled;
    }
}
