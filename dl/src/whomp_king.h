#pragma once

#include <sm64.h>
extern "C"
{
    #include <game/object_list_processor.h>
}

class WhompKing : Object
{
private:
    void Init();
    void Step();
    static void sInit() { reinterpret_cast<WhompKing*>(gCurrentObject)->Init(); }
    static void sStep() { reinterpret_cast<WhompKing*>(gCurrentObject)->Step(); }

public:
    static unsigned Behavior[];
};
