#pragma once

#include <sm64.h>
extern "C"
{
    #include <game/object_list_processor.h>
}

extern void preGreenSwitchBoard();
class GreenSwitchBlockResetter : Object
{
private:
    void Init();
    void Step();
    static void sInit() { reinterpret_cast<GreenSwitchBlockResetter*>(gCurrentObject)->Init(); }
    static void sStep() { reinterpret_cast<GreenSwitchBlockResetter*>(gCurrentObject)->Step(); }

public:
    static int Behavior[];
};
