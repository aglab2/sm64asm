#include "moving.h"
extern "C"
{
    #include "game/object_helpers.h"
}
#include "ctl.h"
#include "object_fields.h"
#include "triplet.h"

#include "rm.h"

void Moving::Init()
{
    f32 d;
    oMovingCtlObject = obj_find_nearest_object_with_behavior((const BehaviorScript*) 0x408000, &d);
    oMovingPropeller = spawn_object_relative(0, 0, -100.f, 0, this, 236, (const BehaviorScript*) 0x408030);
    oCollisionDistance = 320.f;
    oDrawingDistance = 10000.f;
}

static triplet Path[]
{
    { -250, -2250, 250 },
    { -250, 250, 250 },
    { -250, 250, 4250 },
    { -250, 2250, 4250 },
    { -250, 2250, 12750 },
};

static float Speed = 7.f;

void Moving::Step()
{
    float* start, *end, *pos, *vel;
    if (!oMovingCtlObject->oCtlState)
    {
        start = (float*) &Path[oBehParams2ndByte].x;
        end   = (float*) &Path[oBehParams2ndByte + 1].x;
    }
    else
    {
        start = (float*) &Path[oBehParams2ndByte + 1].x;
        end   = (float*) &Path[oBehParams2ndByte].x;
    }
    pos = (float*) &oPos.x;
    vel = (float*) &oVel.x;

    bool done = false;
    for (int i = 1; i < 3; i++)
    {
        if (start[i] == end[i])
        {
            vel[i] = 0;
            pos[i] = start[i];
        }
        else if (start[i] < end[i])
        {
            vel[i] = Speed;
            pos[i] += vel[i];
            done = pos[i] > end[i];
        }
        else
        {
            vel[i] = -2 * Speed;
            pos[i] += vel[i];
            done = pos[i] < end[i];
        }
    }

    if (done)
    {
        pos[1] = end[1]; pos[2] = end[2];
        oBehParams2ndByte += oMovingCtlObject->oCtlState ? -1 : 1;
        if (oBehParams2ndByte < 0)
        {
            oBehParams2ndByte = sizeof(Path) / sizeof(*Path) - 2;
            pos[1] = Path[oBehParams2ndByte + 1].y;
            pos[2] = Path[oBehParams2ndByte + 1].z;
        }

        if (oBehParams2ndByte == sizeof(Path) / sizeof(*Path) - 1)
        {
            oBehParams2ndByte = 0;
            pos[1] = Path[0].y;
            pos[2] = Path[0].z;
        }
    }

    oMovingPropeller->oPosX = oPosX;
    oMovingPropeller->oPosY = oPosY - 50.f;
    oMovingPropeller->oPosZ = oPosZ;
}

uintptr_t Moving::Behavior[] = 
{
    0x11010001,
    0x2a000000, SQUARE_COLL_PTR,
    0x0C000000, (uintptr_t) sInit,
    0x08000000,
    0x0C000000, (uintptr_t) sStep,
    0x0C000000, 0x803839cc,
    0x09000000,
};