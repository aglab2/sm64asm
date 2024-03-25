#pragma once

#include <sm64.h>
extern "C"
{
    #include <game/object_list_processor.h>
}

class EndscreenBlocker : Object
{
private:
    void Init();
    void Step();
    static void sInit() { reinterpret_cast<EndscreenBlocker*>(gCurrentObject)->Init(); }
    static void sStep() { reinterpret_cast<EndscreenBlocker*>(gCurrentObject)->Step(); }

public:
    static int Behavior[];
};
