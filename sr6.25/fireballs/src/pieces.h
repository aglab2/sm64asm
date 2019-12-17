#pragma once
#include <sm64.h>

class Pieces : MObject
{
    void Step();
    static void sStep() { reinterpret_cast<Pieces*>(M64_CURR_OBJ_PTR)->Step(); }

public:
    static int Behavior[];
};