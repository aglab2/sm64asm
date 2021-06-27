#pragma once

extern "C"
{
    #include "types.h"
    #include "game/object_list_processor.h"
}
#include "object_fields.h"

class VSwitch : Object
{
    using Type = VSwitch;

    enum Actions
    {
        PURPLE_SWITCH_IDLE,
        PURPLE_SWITCH_PRESSED,
        PURPLE_SWITCH_TICKING,
    };

#define oVSwitchCtlObject OBJECT_FIELD_OBJ(0x1b)
#define oVSwitchTimer OBJECT_FIELD_S32(0x1c)

    void ScaleOverTime(s32 a0, s32 a1, f32 sp10, f32 sp14);

#define PROXIED_FUNCTION(x) void x(); static void s##x() { return reinterpret_cast<Type*>(gCurrentObject)->x(); }
    PROXIED_FUNCTION(Init)
    PROXIED_FUNCTION(Step)
#undef PROXIED_FUNCTION

public:
    static uintptr_t Behavior[];
};