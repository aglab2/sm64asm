#include "bookshelf.h"
extern "C"
{
    #include "game/object_helpers.h"
    #include "audio/external.h"
}

void BookShelf::Init()
{
    scale_object(this, 1.4f);
    oBookShelfBookCount = 4;
}

void BookShelf::Step()
{
    if (oBookShelfBookCount == 0)
    {
        oPosZ += 10.f;
        if (oPosZ > 5000.f)
        {
            activeFlags = 0;
        }
    }
}

uintptr_t BookShelf::Behavior[] = {
    0x11010001,
    0x0c000000, (uintptr_t) sInit,
    0x2a000000, 0x0707A360,
    0x08000000,
    0x0c000000, (uintptr_t) sStep,
    0x0c000000, 0x803839cc,
    0x09000000,
};