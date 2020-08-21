#include "mips.h"
extern "C"
{
    #include "game/object_helpers.h"
    #include "engine/surface_collision.h"
    #include "engine/math_util.h"
    #include "game/level_update.h"
}
#include "obj_ctl.h"

extern "C" s32 object_step(void);

void MIPS::Init()
{
    scale_object(this, 1.2f);
    oForwardVel = 5.f;
    obj_compute_vel_xz();
    SetObjAnimation(1);
}

void MIPS::Move()
{
    Surface* surf;
    auto floorY = find_floor(oPosX, oPosY, oPosZ, &surf);
    if (floorY != oPosY)
    {
        if (oPosY > 2000.f)
        {
            oGravity = -500.f;
        }
        else
        {
            oGravity = -5.f;
        }
    }
    obj_move_using_vel_and_gravity();
    if (floorY > oPosY)
    {
        oPosY = floorY;
        oVelY = 0;
        oGravity = 0;
    }
}

void MIPS::Step()
{
    if (oDistanceToMario < 125.f)
    {
        ObjectCtl::SpawnParticlesAt(this);
        activeFlags = 0;
        return;
    }

    Move();

    auto dist = oPosX * oPosX + oPosZ * oPosZ;
    if (dist < 1500.f)
    {
        gMarioStates->health -= 0x100;
        activeFlags = 0;
        return;
    }
}

uintptr_t MIPS::Behavior[] = 
{
    0x11010041,
    0x27260000, 0x07015724,
    0x0C000000, (uintptr_t) sInit,
    0x08000000,
    0x0C000000, (uintptr_t) sStep,
    0x09000000
};

void BigMIPS::Init()
{
    obj_compute_vel_xz();
    SetObjAnimation(1);
}

void BigMIPS::SpawnClone(int off)
{
    auto scale = header.gfx.scale[0];
    if (scale <= 1.3f)
        return;

    auto dist = sqrtf(oPosX * oPosX + oPosZ * oPosZ);
    auto angle = (u16) (oFaceAngleYaw - 0x8000 + off);
    auto rabbit = spawn_object(this, 0xf3, (const BehaviorScript*) BigMIPS::Behavior);
    rabbit->oPosX = dist * sins(angle);
    rabbit->oPosY = oPosY;
    rabbit->oPosZ = dist * coss(angle);

    rabbit->oFaceAngleYaw = angle + 0x8000;
    rabbit->oMoveAngleYaw = rabbit->oFaceAngleYaw;
    rabbit->oForwardVel = oForwardVel * 2.f;
    scale_object(rabbit, scale / 2.f);
}

void BigMIPS::Step()
{
    auto scale = header.gfx.scale[0];
    if (oDistanceToMario < sqrtf(scale) * 100.f)
    {
        ObjectCtl::SpawnParticlesAt(this);
        SpawnClone(0x2000);
        SpawnClone(-0x2000);
        activeFlags = 0;
        return;
    }
    
    MIPS::Move();

    auto dist = oPosX * oPosX + oPosZ * oPosZ;
    if (dist < 1000.f)
    {
        gMarioStates->health -= 0x100 * scale;
        activeFlags = 0;
        return;
    }
}

uintptr_t BigMIPS::Behavior[] = 
{
    0x11010041,
    0x27260000, 0x07015724,
    0x0C000000, (uintptr_t) sInit,
    0x08000000,
    0x0C000000, (uintptr_t) sStep,
    0x09000000
};

