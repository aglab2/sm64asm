#pragma once

#include "object_fields.h"
extern "C"
{
    #include "types.h"
    #include "game/object_list_processor.h"
}

class F3DParser : Object
{
    #define oCullDistance OBJECT_FIELD_F32(0x1b)

public:
    using Proxy = void(*)(void);
    
#define oChildren (&OBJECT_FIELD_OBJ(0x1B))

    enum Actions
    {
        STATIC,
        EXPLODE,
    };

private:
#define OBJ_DEFINE_FUNC_WITH_PROXY(fn) void fn(); static void s##fn() { reinterpret_cast<F3DParser*>(gCurrentObject)->fn(); }
    OBJ_DEFINE_FUNC_WITH_PROXY(Init)
    OBJ_DEFINE_FUNC_WITH_PROXY(Step)
#undef OBJ_DEFINE_FUNC_WITH_PROXY

    int PerformCulling(void* from, void* to);
    void AdjustCulling();
    void CopyDL(void* from, void* to);

public:
    static uintptr_t Behavior[];
};