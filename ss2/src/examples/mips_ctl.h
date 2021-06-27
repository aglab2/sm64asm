#pragma once

extern "C"
{
    #include "types.h"
    #include "game/object_list_processor.h"
}
#include "object_fields.h"

class MIPSCtl : Object
{
    using Type = MIPSCtl;
    enum Actions
    {
        WELCOME,
        SPIRAL,
        ROMBS,
        FINAL,
    };

#define PROXIED_FUNCTION(x) void x(); static void s##x() { return reinterpret_cast<Type*>(gCurrentObject)->x(); }

    PROXIED_FUNCTION(Init)
    PROXIED_FUNCTION(Step)
    
    PROXIED_FUNCTION(Welcome)
    PROXIED_FUNCTION(Spiral)
    PROXIED_FUNCTION(Rombs)
    PROXIED_FUNCTION(Final)
    
    static void (*sProxies[])(void);

#undef PROXIED_FUNCTION

    void SpawnMIPS(int path);

public:
    static uintptr_t Behavior[];
};