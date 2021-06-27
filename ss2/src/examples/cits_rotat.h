#pragma once

extern "C"
{
    #include "types.h"
    #include "game/object_list_processor.h"
}
#include "object_fields.h"

class CITSRotat : public Object
{
protected:
    using Type = CITSRotat;

#define PROXIED_FUNCTION(x) void x(); static void s##x() { return reinterpret_cast<Type*>(gCurrentObject)->x(); }

    PROXIED_FUNCTION(Init)
    PROXIED_FUNCTION(Step)

#undef PROXIED_FUNCTION
};

class CITSRotat1 : public CITSRotat
{
public:
    static uintptr_t Behavior[];
};

class CITSRotat2 : public CITSRotat
{
public:
    static uintptr_t Behavior[];
};
