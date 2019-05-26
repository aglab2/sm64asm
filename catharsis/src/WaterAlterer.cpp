#include "WaterAlterer.h"
#include <water.h>

void WaterAlterer::Init()
{
    WaterBoxHeader* header = M64_WATER_BOX_LIST;
    if (header == nullptr)
        return;

    int id = bparam1;
    if (id >= header->count)
        return;

    posInit.y = header->boxes[bparam1].y;
}

void WaterAlterer::Step()
{
    WaterBoxHeader* header = M64_WATER_BOX_LIST;
    if (header == nullptr)
        return;

    int id = bparam1;
    if (id >= header->count)
        return;
    
    if (bparam2 == 0)
        return;

    header->boxes[id].y = posInit.y + sinf((float)timer / (float)bparam2) * (float)bparam34;
}

int WaterAlterer::Behavior[] =
{
    0x0C000000, (int) sInit,
    0x08000000,
    0x0C000000, (int) sStep,
    0x09000000,    
};