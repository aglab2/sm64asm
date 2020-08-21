#include "c8_deathfloor.h"

void C8DeathFloor::Init()
{
    oDrawingDistance = 40000.f;

    auto x = (0 != (oBehParams & 0xff000000));
    auto z = (0 != (oBehParams & 0x00ff0000));

    if (x)
        oVelX = 24.0;

    if (z)
        oVelZ = x ? -19.0 : 19.0;
}

void C8DeathFloor::Step()
{
    oPosX += oVelX;
    oPosZ += oVelZ;

    auto doSwitch = 0 == (oTimer & 127);
    if (doSwitch)
    {
        oVelX = -oVelX;
        oVelZ = -oVelZ;
    }
}

uintptr_t C8DeathFloor::Behavior[] = {
    0x11010001,
    0x0c000000, (uintptr_t) sInit,
    0x2a000000, 0x07061DC0,
    0x08000000,
    0x0c000000, (uintptr_t) sStep,
    0x0c000000, 0x803839cc,
    0x09000000,
};