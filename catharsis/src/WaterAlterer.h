#pragma once

#include <sm64.h>

class WaterAlterer : public MObject
{
private:
    void Init();
    void Step();

    static void sInit() { reinterpret_cast<WaterAlterer*>(M64_CURR_OBJ_PTR)->Init(); }
    static void sStep() { reinterpret_cast<WaterAlterer*>(M64_CURR_OBJ_PTR)->Step(); }

public:
    static int Behavior[];
};