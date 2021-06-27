#pragma once

extern "C"
{
    #include "types.h"
    #include "game/object_list_processor.h"
}
#include "object_fields.h"

class Moving : Object
{
    using Type = Moving;

#define oMovingCtlObject OBJECT_FIELD_OBJ(0x1b)
#define oMovingPropeller OBJECT_FIELD_OBJ(0x1c)

#define PROXIED_FUNCTION(x) void x(); static void s##x() { return reinterpret_cast<Type*>(gCurrentObject)->x(); }
    PROXIED_FUNCTION(Init)
    PROXIED_FUNCTION(Step)
#undef PROXIED_FUNCTION

public:
    static uintptr_t Behavior[];
};