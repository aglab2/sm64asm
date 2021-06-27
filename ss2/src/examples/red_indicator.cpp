#include "red_indicator.h"
extern "C"
{
    #include "game/game.h"
    #include "game/object_helpers.h"
    #include "game/print.h"
}

#define oEnabled OBJECT_FIELD_S32(0x1b)

void RedIndicator::Step()
{
    if (gControllers->buttonPressed & L_TRIG)
        oEnabled = !oEnabled;

    if (oEnabled)
    {
        auto red = obj_nearest_object_with_behavior((const BehaviorScript*) 0x13003EAC);
        if (red)
        {
            auto dist = dist_between_objects(gMarioObject, red);
            print_text_fmt_int(20, 20, "RED %d", dist / 100.f);
        }
    }
}

uintptr_t RedIndicator::Behavior[] = {
    0x08000000,
    0x0c000000, (uintptr_t) sStep,
    0x09000000,
};