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

    PROXIED_FUNCTION(Phase1)
    PROXIED_FUNCTION(TrollDeath)
    PROXIED_FUNCTION(Avoidance)
    PROXIED_FUNCTION(Phase2)
    PROXIED_FUNCTION(Dead)
	
#undef PROXIED_FUNCTION

	static void (*sActions[])(void);

public:
    static uintptr_t Behavior[];
};