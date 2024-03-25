#pragma once

#include <sm64.h>
extern "C"
{
    #include <game/object_list_processor.h>
}

class BlueStarBlock : Object
{
private:
    void Init();
    void Step();
    static void sInit() { reinterpret_cast<BlueStarBlock*>(gCurrentObject)->Init(); }
    static void sStep() { reinterpret_cast<BlueStarBlock*>(gCurrentObject)->Step(); }

public:
    static int Behavior[];
};
