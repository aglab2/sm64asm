#pragma once

extern "C"
{
    #include "types.h"
    #include "game/object_list_processor.h"
}
#include "object_fields.h"

class TwoD : public Object
{
protected:
    void Init();
    static void sInit() { reinterpret_cast<TwoD*>(gCurrentObject)->Init(); }
    void Step();
    static void sStep() { reinterpret_cast<TwoD*>(gCurrentObject)->Step(); }

public:
    static int Behavior[];
};