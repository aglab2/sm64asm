#pragma once

#include <sm64.h>
extern "C"
{
    #include <game/object_list_processor.h>
}

class ChangeMusic : Object
{
private:
    void Init();
    void Step();
    static void sInit() { reinterpret_cast<ChangeMusic*>(gCurrentObject)->Init(); }
    static void sStep() { reinterpret_cast<ChangeMusic*>(gCurrentObject)->Step(); }

public:
    static int Behavior[];
};
