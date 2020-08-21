#include "c1_upwards.h"
extern "C"
{
    #include "game/level_update.h"
    #include "game/memory.h"
    #include "game/object_helpers.h"
    #include "game/object_helpers2.h"
    #include "game/print.h"
    #include "engine/math_util.h"
}

#define oWasSpawned OBJECT_FIELD_S32(0x1b)
#define oPrintLookBack OBJECT_FIELD_S32(0x1c)
#define oGoBackwards OBJECT_FIELD_F32(0x1d)

#define INITIAL (oHomeY == 0.f)

static triplet gPositions[] = {
    { 6708, -1200, -923 },
    { 5874, -1200, -95 },
    { 4720, -1200, 62 }, // init
    { 3701, -1200, -471 },
    { 3166, -1200, -1569 },
};

static u16 gRotations[] = {
    (0x10000 / 360) * 63,
    (0x10000 / 360) * 25,
    (0x10000 / 360) * 350, // init
    (0x10000 / 360) * 314,
    (0x10000 / 360) * 278,
};

void C1Upwards::Init()
{
    oDrawingDistance = 40000.f;
    oCollisionDistance = 800.f;
    if (INITIAL)
        oBehParams2ndByte = 2;
}

void C1Upwards::SpawnNext()
{
    if (oBehParams2ndByte == 0 || oBehParams2ndByte == 1)
        return;

    oWasSpawned = true;
    auto me = spawn_object(this, 0xf1, (const BehaviorScript*) 0x4080CC);
    me->oGoBackwards = oGoBackwards;
    me->oBehParams2ndByte = oBehParams2ndByte + (me->oGoBackwards ? -1 : 1);
    if (me->oBehParams2ndByte == 5)
    {
        me->oBehParams2ndByte = 3;
        me->oGoBackwards = true;
        oPrintLookBack = true;
    }

    *(triplet*) &me->oPosX = gPositions[me->oBehParams2ndByte];
    me->oHomeY = oHomeY ? (oHomeY + 350.f) : (-300.f);
    me->oFaceAngleYaw = gRotations[me->oBehParams2ndByte];
}

void C1Upwards::Step()
{
    if (oPrintLookBack && oTimer < 140)
        print_text_centered(120, 20, "LOOK BEHIND");

    if (INITIAL)
    {
        if (!oWasSpawned && gMarioStates->pos[1] > 0 && obj_is_mario_on_platform())
            SpawnNext();

        if (gMarioStates->pos[1] < 0)
            oWasSpawned = false;
    }
    else
    {
        auto period = 150;

        if (oTimer < 80)
        {
            auto pos = sins(oTimer * period);
            oPosY = oHomeY + pos * 1000.f;
        }
        else if (!oWasSpawned && obj_is_mario_on_platform())
            SpawnNext();

        // if (oPosY < oHomeY - 500.f)
        //    activeFlags = 0;
        if (gMarioStates->pos[1] < -393.f)
            activeFlags = 0;
    }
}

uintptr_t C1Upwards::Behavior[] = 
{
    0x0c000000, (uintptr_t) sInit,
    0x11010001,
    0x2a000000, 0x07013C70,
    0x08000000,
    0x0c000000, (uintptr_t) sStep,
    0x0c000000, 0x803839cc,
    0x09000000,
};