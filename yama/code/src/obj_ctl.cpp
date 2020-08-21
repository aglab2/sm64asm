#include "obj_ctl.h"

extern "C"
{
    #include "types.h"
    #include "game/object_list_processor.h"
    #include "game/object_helpers.h"
    #include "engine/behavior_script.h"
}
#include "object_fields.h"

void ObjectCtl::SpawnParticlesAt(Object* obj)
{
    auto info = (SpawnParticlesInfo*) (0x8033032C);
    auto numParticles = info->count;

    if (gPrevFrameObjectCount > 150 && numParticles > 10)
        numParticles = 10;

    if (gPrevFrameObjectCount > 210)
        numParticles = 0;

    for (auto i = 0; i < numParticles; i++) {
        auto scale = RandomFloat() * (info->sizeRange * 0.1f) + info->sizeBase * 0.1f;
        auto particle = spawn_object(obj, info->model, (const BehaviorScript*) 0x130007dc);

        particle->oBehParams2ndByte = info->behParam;
        particle->oMoveAngleYaw = RandomU16();
        particle->oGravity = info->gravity;
        particle->oDragStrength = info->dragStrength;

        particle->oPosY += info->offsetY;
        particle->oForwardVel = RandomFloat() * info->forwardVelRange + info->forwardVelBase;
        particle->oVelY = RandomFloat() * info->velYRange + info->velYBase;

        scale_object_xyz(particle, scale, scale, scale);
    }
}