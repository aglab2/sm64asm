#pragma once

extern "C"
{
    #include "types.h"
    #include "game/object_list_processor.h"
}
#include "object_fields.h"

class Key : Object
{
#define oKeyBox OBJECT_FIELD_OBJ(0x1b)

    using Type = Key;
    enum Actions
    {
        INSIDE,
        DEAD,
        ACTIVE,
    };

#define PROXIED_FUNCTION(x) void x(); static void s##x() { return reinterpret_cast<Type*>(gCurrentObject)->x(); }

    PROXIED_FUNCTION(Init)
    PROXIED_FUNCTION(Step)
    PROXIED_FUNCTION(Room)

#undef PROXIED_FUNCTION

    void InsideBoo();
    void DeadBoo();
    void Active();

public:
    static uintptr_t Behavior[];
};