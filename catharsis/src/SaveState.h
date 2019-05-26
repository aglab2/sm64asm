#pragma once

#include <sm64.h>

class SaveState : public MObject
{
public:
    static void Save();
    static void Load();

private:
    void Init();
    void Step();

    static void sInit() { reinterpret_cast<SaveState*>(M64_CURR_OBJ_PTR)->Init(); }
    static void sStep() { reinterpret_cast<SaveState*>(M64_CURR_OBJ_PTR)->Step(); }

public:
    static int Behavior[];
};