#pragma once

extern "C"
{
    #include "types.h"
    #include "game/object_list_processor.h"
}
#include "object_fields.h"

class C9PuzzleCoin : public Object
{
    using Type = C9PuzzleCoin;

#define PROXIED_FUNCTION(x) void x(); static void s##x() { return reinterpret_cast<Type*>(gCurrentObject)->x(); }

    PROXIED_FUNCTION(Init)
    PROXIED_FUNCTION(Step)
    
#undef PROXIED_FUNCTION

public:
    static uintptr_t Behavior[];
};