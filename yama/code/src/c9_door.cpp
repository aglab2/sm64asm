#include "c9_door.h"
extern "C"
{
    #include "game/level_update.h"
}
#include "f2_scroll.h"

void C9Door::Step()
{
    auto stars = gMarioStates->numStars;
    if (stars >= 100)
    {
        activeFlags = 0;
    }

    Scroll(1, 1, 0x0701A250);
}

uintptr_t C9Door::Behavior[] = 
{
    0x08000000,
    0x2a000000, 0x0701A2F0,
    0x0c000000, (uintptr_t) sStep,
    0x0C000000, 0x803839cc,
    0x09000000
};