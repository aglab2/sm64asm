#pragma once

extern "C"
{
    #include "types.h"
    #include "game/object_list_processor.h"
}
#include "object_fields.h"

class Ctl : Object
{
    using Type = Ctl;

#define oCtlState OBJECT_FIELD_S32(0x1b)
#define oCtlQSRotatSpeed OBJECT_FIELD_S32(0x1c)
#define oCtlHealTimer OBJECT_FIELD_S32(0x1d)

#define PROXIED_FUNCTION(x) void x(); static void s##x() { return reinterpret_cast<Type*>(gCurrentObject)->x(); }
    PROXIED_FUNCTION(Init)
    PROXIED_FUNCTION(Step)
#undef PROXIED_FUNCTION

public:
    static uintptr_t Behavior[];
};