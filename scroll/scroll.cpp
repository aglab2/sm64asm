#include "types.h"
extern "C"
{
    #include "game/object_list_processor.h"
    #include "game/memory.h"
    #include "engine/math_util.h"
}
#include "object_fields.h"

union ScrollCtl
{
    struct
    {
        unsigned int pad   : 16;
        unsigned int voff  : 4;
        unsigned int type  : 4;
        unsigned int cycle : 8;
    };
    unsigned int v;
};

#define oParam OBJECT_FIELD_S32(0x1b)

// This weird cast is needed for clang to not generate useless overflow code
static auto toInt(float val)
{
    return (int) (long) val;
}

static auto toUInt(float val)
{
    return (unsigned int) (long) val;
}

// allowed short distances are [-32768, 32767]
static auto addCheckFix(short* ptr, short amount)
{
    int data = *ptr;
    data += amount;
    auto overflowed = (data > 32767 || data < -32768);
    *ptr = data;
    return overflowed;
}

void scroll()
{
    auto cnt = toInt(gCurrentObject->oPosX);
    ScrollCtl ctl { .v = toUInt(gCurrentObject->oPosY) };
    auto spd = toInt(gCurrentObject->oPosZ);
    auto uv = ctl.voff >= 8;

    auto vptr = (char*) segmented_to_virtual((void*) gCurrentObject->oBehParams);
    vptr += ctl.voff;

    auto vptrEnd = vptr + cnt * 0x10;
    switch (ctl.type)
    {
    // Classic scroll
    case 0:
    {
        // honestly this implementation is awkward, I just scroll back coordinates which is barely something anyone need
        if (!uv)
        {
            if (gCurrentObject->oTimer == ctl.cycle)
            {
                gCurrentObject->oTimer = 0;
                spd -= (ctl.cycle * spd);
            }
        }
    }
    break;
    // Sine scroll
    case 1:
    {
        // modulate the speed by sine wave
        spd *= sins(gCurrentObject->oTimer * (ctl.cycle * 0x20 + 0x10));
    }
    break;
    // Jump scroll
    case 2:
    {
        // scroll only if cycle hit
        auto timer = gCurrentObject->oTimer;
        if (timer != ctl.cycle + 1)
            return;

        gCurrentObject->oTimer = 0;
    }
    break;
    }

    // do it
    for (auto ptr = vptr; ptr != vptrEnd; ptr += 0x10)
    {
        // Overflow checks only makes sense for UVs scrolling, for position scrolls it is going to create weirdness
        auto overflow = addCheckFix((short*) ptr, spd);
        if (uv && overflow)
        {
            // If UVs, scroll backwards by 0x800 which means 64 pixels (which is good enough?)
            for (auto ptrf = vptr; ptrf != vptrEnd; ptrf += 0x10)
            {
                *(short*)ptrf += (spd > 0 ? -0x800 : 0x800);
            }
        }
    }
}