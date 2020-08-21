#include "aglab_camera.h"
extern "C"
{
    #include "game/level_update.h"
    #include "game/object_helpers.h"
}

extern s16 s8DirModeYawOffset;

void AglabCamera::Init()
{
    activeFlags = 0;
    s8DirModeYawOffset = (gMarioStates->faceAngle[1] + 0x9000) & 0xc000;
}

uintptr_t AglabCamera::Behavior[] = 
{
    0x0c000000, (uintptr_t) sInit,
    0x08000000,
    0x09000000,
};