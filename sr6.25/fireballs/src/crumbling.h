#pragma once

#include <sm64.h>

class Crumbling : MObject
{
    void Init();
    void WasStepped();
    void FallingDown();
    void Dying();

    void Step();
    static void sStep() { reinterpret_cast<Crumbling*>(M64_CURR_OBJ_PTR)->Step(); }

public:
    static int Behavior[];
};