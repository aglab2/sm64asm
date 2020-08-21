#include "wall_translucer.h"
extern "C"
{
    #include "game/level_update.h"
    #include "game/print.h"
    #include "game/memory.h"
}

static const uintptr_t cSegAddresses[] = {
    0x0E0933C8, 0x0E0932B0, 0x0E092E90, 
    0x0E0934B8, 0x0E0935A8, 0x0E093698,
};

static int YSTatus(float y)
{
    return y < 1860.f;
}

static int ZStatus(float z)
{
    if (z < -4330.f)
        return 0;
    if (z < -2469.f)
        return 1;
    
    return 2;
}

void WallTranslucer::Step()
{
    for (int i = 0; i < sizeof(cSegAddresses) / sizeof(uintptr_t); i++)
    {
        auto ptr = (char*) segmented_to_virtual((void*) cSegAddresses[i]);
        ptr[7] = 0;
    }

    if (gMarioObject->oPosX > 2360.f)
    {
        auto y = YSTatus(gMarioObject->oPosY);
        auto z = ZStatus(gMarioObject->oPosZ);

        auto ptrseg = (void*) cSegAddresses[z + y * 3];
        auto ptr = (char*) segmented_to_virtual(ptrseg);
        ptr[7] = 0xff;
    }
}

uintptr_t WallTranslucer::Behavior[] = 
{
    0x08000000,
    0x0c000000, (uintptr_t) sStep,
    0x09000000,
};