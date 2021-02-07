#pragma once

extern "C"
{
    #include "types.h"
    #include "game/object_list_processor.h"
}
#include "object_fields.h"

class CheezeZap : Object
{
protected:
    void Init();
    static void sInit() { reinterpret_cast<CheezeZap*>(gCurrentObject)->Init(); }
    void Step();
    static void sStep() { reinterpret_cast<CheezeZap*>(gCurrentObject)->Step(); }

public:
    static int Behavior[];
};
