#include "c1_moving.h"
extern "C"
{
    #include "game/memory.h"
    #include "engine/math_util.h"
}

void C1Moving::Init()
{
    oHomeX = oPosX;
    oDrawingDistance = 40000.f;
    oCollisionDistance = 800.f;
}

void C1Moving::Step()
{
    auto amplitude = 350.f;
    auto period = 100;

    auto pos = sins(oTimer * period);
    oPosX = oHomeX + pos * amplitude;
}

uintptr_t C1Moving::Behavior[] = 
{
    0x0c000000, (uintptr_t) sInit,
    0x11010001,
    0x2a000000, 0x07012120,
    0x08000000,
    0x0c000000, (uintptr_t) sStep,
    0x0c000000, 0x803839cc,
    0x09000000,
};