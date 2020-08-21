#pragma once

extern "C"
{
    #include "types.h"
    #include "game/object_list_processor.h"
}
#include "object_fields.h"

class B3FCtl : Object
{
    using Type = B3FCtl;

#define PROXIED_FUNCTION(x) void x(); static void s##x() { return reinterpret_cast<Type*>(gCurrentObject)->x(); }

    PROXIED_FUNCTION(Init)
    PROXIED_FUNCTION(Step)

#undef PROXIED_FUNCTION

    void Phase1();
    void TrollDeath();
    void Avoidance();
    void Phase2();

public:
    static uintptr_t Behavior[];
};