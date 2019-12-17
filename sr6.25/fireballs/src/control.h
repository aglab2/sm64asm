#pragma once
#include <sm64.h>

class Control : MObject
{
    void Set2DState();
    void Check2DCollision();
    void CheckBowserPosition();
    void SpawnFireBalls();
    void ControlBowser();
    void ControlBowserFini();

    void Init();
    void Step();
    
    static void sInit() { reinterpret_cast<Control*>(M64_CURR_OBJ_PTR)->Init(); }
    static void sStep() { reinterpret_cast<Control*>(M64_CURR_OBJ_PTR)->Step(); }

public:
    static int Behavior[];
};