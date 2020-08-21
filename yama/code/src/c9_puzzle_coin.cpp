#include "c9_puzzle_coin.h"
extern "C"
{
    #include "game/print.h"
}

void C9PuzzleCoin::Step()
{
    oAnimState++;
    if (oDistanceToMario < 150.f)
        activeFlags = 0;
}

uintptr_t C9PuzzleCoin::Behavior[] = {
    0x21000000,
    0x11010041,
    0x08000000,
    0x0c000000, (uintptr_t) sStep,
    0x09000000,
};
