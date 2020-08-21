#include "b1_fight_ctl.h"
extern "C"
{
    #include "game/level_update.h"
    #include "game/object_helpers.h"
}

#define oBowser OBJECT_FIELD_OBJ(0x1d)

enum Actions
{
    INIT,
    DONE,
};

void B1FightCtl::Init()
{
    TwoD::Init();

    f32 dist;
    oBowser = obj_find_nearest_object_with_behavior((BehaviorScript*) 0x13001850, &dist);
    oBehParams = 0x4000;
}

void B1FightCtl::Step()
{
    if (oAction == INIT)
    {
        if (gMarioObject->oPosZ < -3700.f)
        {
            oAction = DONE;
            oBehParams = 0xc000;
            oPosX = 0;
            gMarioStates->pos[0] = 0;
            gMarioStates->pos[1] = 3487.f;
            gMarioStates->pos[2] = -994.f;
        }
    }
    
    TwoD::Step();
    oBowser->oPosX = 0;
}

uintptr_t B1FightCtl::Behavior[] = {
    0x0c000000, (uintptr_t) sInit,
    0x08000000,
    0x0c000000, (uintptr_t) sStep,
    0x09000000,
};