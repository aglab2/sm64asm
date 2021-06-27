#pragma once

extern "C"
{
    #include "types.h"
    #include "game/object_list_processor.h"
}
#include "object_fields.h"

class RoomsColl : Object
{
protected:
    void PlaySequence(int seq);

    void Init();
    static void sInit() { reinterpret_cast<RoomsColl*>(gCurrentObject)->Init(); }
    void Step();
    static void sStep() { reinterpret_cast<RoomsColl*>(gCurrentObject)->Step(); }

public:
    static int Behavior[];
};