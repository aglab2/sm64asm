#pragma once

extern "C"
{
    #include "types.h"
    #include "game/object_list_processor.h"
}
#include "object_fields.h"

class MIPS : public Object
{
    using Type = MIPS;

#define PROXIED_FUNCTION(x) void x(); static void s##x() { return reinterpret_cast<Type*>(gCurrentObject)->x(); }

    PROXIED_FUNCTION(Init)
    PROXIED_FUNCTION(Step)

#undef PROXIED_FUNCTION

protected:
    void Move();

public:
    static uintptr_t Behavior[];
};

class BigMIPS : public MIPS
{
    using Type = BigMIPS;

#define PROXIED_FUNCTION(x) void x(); static void s##x() { return reinterpret_cast<Type*>(gCurrentObject)->x(); }

    PROXIED_FUNCTION(Init)
    PROXIED_FUNCTION(Step)

#undef PROXIED_FUNCTION

    void SpawnClone(int off);

public:
    static uintptr_t Behavior[];
};
