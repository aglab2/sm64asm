#include "hud_relocator.h"
extern "C"
{
    #include "game/memory.h"
    #include "string.h"
}

void HUDRelocator::Init()
{
    auto oldHud = segmented_to_virtual((void*) 0x02000000);
    auto newHud = segmented_to_virtual((void*) oBehParams);
    memcpy(oldHud, newHud, 0x4400);
    activeFlags = 0;
}

uintptr_t HUDRelocator::Behavior[] = 
{
    0x0c000000, (uintptr_t) sInit,
    0x08000000,
    0x09000000,
};