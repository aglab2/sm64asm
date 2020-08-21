#include "aglab_pillar.h"
extern "C"
{
    #include "game/level_update.h"
}

constexpr float sDropSpeed = 9.f;

void AglabPillar::Init()
{
    oHomeY = oPosY;
    oCollisionDistance = 1200.f;
}

void AglabPillar::Step()
{
    auto& mario = gMarioStates[0];
    auto floor = mario.floor;

    if (floor && floor->type == 0x37 && mario.floorHeight == mario.pos[1])
    {
        oPosY = oHomeY;
    }
    else if (oPosY > -4000.f)
    {
        oPosY -= sDropSpeed;
    }
}

uintptr_t AglabPillar::Behavior[] = 
{
    0x11010001,
    0x0c000000, (uintptr_t) sInit,
    0x2a000000, 151003808,
    0x08000000,
    0x0c000000, (uintptr_t) sStep,
    0x0c000000, 0x803839cc,
    0x09000000,
};