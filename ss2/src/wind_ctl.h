#pragma once

extern "C"
{
    #include "types.h"
    #include "game/object_list_processor.h"
}
#include "object_fields.h"

class WindCtl : Object
{
    using Type = WindCtl;

#define oWindParticlesCtlObject OBJECT_FIELD_OBJ(0x1b)

#define PROXIED_FUNCTION(x) void x(); static void s##x() { return reinterpret_cast<Type*>(gCurrentObject)->x(); }
    PROXIED_FUNCTION(Init)
    PROXIED_FUNCTION(Step)
#undef PROXIED_FUNCTION

    void SpawnParticles(s16 pitch, s16 yaw, bool dying);

public:
    static uintptr_t Behavior[];
};