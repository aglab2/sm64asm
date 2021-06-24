#include "qs_rotat.h"

extern "C"
{
    #include "game/object_helpers.h"
}
#include "ctl.h"
#include "object_fields.h"

#include "rm.h"

void QSRotat::Init()
{
    f32 d;
    oQSRotatCtlObject = obj_find_nearest_object_with_behavior((const BehaviorScript*) 0x408000, &d);
    oCollisionDistance = 900.f;
    oDrawingDistance = 10000.f;
}

void QSRotat::Step()
{
    constexpr int spdPerFrame = 0x40;
    constexpr int terminalSpeed = 0x800;

    if (!oQSRotatCtlObject->oCtlState)
    {
        if (oQSRotatCtlObject->oCtlQSRotatSpeed < terminalSpeed && gMarioObject->platform == this)
            oQSRotatCtlObject->oCtlQSRotatSpeed += spdPerFrame;
    }
    else
    {
        if (oQSRotatCtlObject->oCtlQSRotatSpeed > 0)
            oQSRotatCtlObject->oCtlQSRotatSpeed -= spdPerFrame;
    }
    
    oAngleVelYaw = oQSRotatCtlObject->oCtlQSRotatSpeed * (oBehParams2ndByte ? 1 : -1);
    oFaceAngleYaw += oAngleVelYaw;
}

uintptr_t QSRotat::Behavior[] = 
{
    0x11010001,
    0x2a000000, QSROTAT_COLL_PTR,
    0x0C000000, (uintptr_t) sInit,
    0x08000000,
    0x0C000000, (uintptr_t) sStep,
    0x0C000000, 0x803839cc,
    0x09000000,
};