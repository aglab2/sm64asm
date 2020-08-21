#include "path_part.h"

#define posNext posInit

void Part::Init()
{
    auto x = posNext.x - pos.x;
    auto y = posNext.y - pos.y;
    auto z = posNext.z - pos.z;
    auto length = sqrtf(x*x + y*y + z*z);
    auto plain = sqrtf(x*x + z*z);

    faceAnglePitch = -atan2s(plain, y);
    faceAngleYaw = atan2s(z, x);

    auto scale = length / 500.0f;
    ScaleXYZ(this, 2.0f, 2.0f, scale);
}

void Part::Step() { }

int Part::Behavior[] = {
    0x11010001,
    0x0c000000, (int) sInit,
    0x08000000,
    0x0c000000, (int) sStep,
    0x09000000,
};
