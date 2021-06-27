#include "mips_ctl.h"
extern "C"
{
    #include "game/obj_behaviors.h"
    #include "game/object_helpers.h"
    #include "game/object_helpers2.h"
    #include "engine/behavior_script.h"
    #include "engine/math_util.h"
    #include "game/print.h"
}
#include "mips.h"

constexpr float cDistance = 2700.f;
constexpr s16 cStartingRotation = 4100;

void (*MIPSCtl::sProxies[])(void) = 
{
    sWelcome,
    sSpiral,
    sRombs,
    sFinal,
};

void MIPSCtl::SpawnMIPS(int path)
{
    auto angle = cStartingRotation + 0x2000 * path;
    auto rabbit = spawn_object(this, 0xf3, (const BehaviorScript*) MIPS::Behavior);

    rabbit->oPosX = cDistance * sins(angle);
    rabbit->oPosY = 2064.f;
    rabbit->oPosZ = cDistance * coss(angle);

    rabbit->oFaceAngleYaw = angle + 0x8000;
    rabbit->oMoveAngleYaw = rabbit->oFaceAngleYaw;
}

void MIPSCtl::Welcome()
{
    if (oTimer == 380)
        oAction++;
        
    if (oTimer == 0)
    {
        for (int i = 0; i < 8; i++)
        {
            SpawnMIPS(i);
        }
    }
}

void MIPSCtl::Spiral()
{
    if (oTimer == 300)
        oAction++;

    if (oTimer % 30 == 0)
    {
        auto path = (oTimer/ 30) % 8;
        SpawnMIPS(path);
    }
}

void MIPSCtl::Rombs()
{
    if (oTimer == 350)
        oAction++;

    if (oTimer % 170 == 0)
    {
        auto start = oTimer % 200 ? 0 : 1;
        for (int i = start; i < 8; i += 2)
        {
            SpawnMIPS(i);
        }
    }
}

void MIPSCtl::Final()
{
    if (oTimer == 0)
    {
        auto angle = cStartingRotation + 0x2000 * (RandomU16() % 8);
        auto rabbit = spawn_object(this, 0xf3, (const BehaviorScript*) BigMIPS::Behavior);

        rabbit->oPosX = cDistance * sins(angle);
        rabbit->oPosY = 2064.f;
        rabbit->oPosZ = cDistance * coss(angle);

        rabbit->oFaceAngleYaw = angle + 0x8000;
        rabbit->oMoveAngleYaw = rabbit->oFaceAngleYaw;
        rabbit->oForwardVel = 0.625f;
        scale_object(rabbit, 10.f);
    }

    if (!obj_nearest_object_with_behavior((const BehaviorScript*) BigMIPS::Behavior))
    {
        create_star(oPosX, oPosY, oPosZ);
        activeFlags = 0;
    }
}

void MIPSCtl::Step()
{
    obj_call_action_function(sProxies);
}

uintptr_t MIPSCtl::Behavior[] = 
{
    0x00040000,
    0x08000000,
    0x0C000000, (uintptr_t) sStep,
    0x09000000
};