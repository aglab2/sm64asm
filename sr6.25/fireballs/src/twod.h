#pragma once

#include <sm64.h>

class TwoD : MObject
{
    void Init();
    static void sInit() { reinterpret_cast<TwoD*>(M64_CURR_OBJ_PTR)->Init(); }
    void Step();
    static void sStep() { reinterpret_cast<TwoD*>(M64_CURR_OBJ_PTR)->Step(); }

public:
    static int Behavior[];
};