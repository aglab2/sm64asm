#include "puffer.h"

#include "types.h"
extern "C"
{
    #include <game/object_helpers.h>
    #include <game/object_list_processor.h>
    #include <engine/behavior_script.h>
    #include <model_ids.h>
}
#include "object_fields.h"

void puffAt(Object* obj, float size, int numParticles)
{
    f32 sizeBase = size;
    f32 sizeRange = size / 20.f;
    f32 forwardVelBase = 40.f;
    f32 forwardVelRange = 5.f;
    f32 velYBase = 30.f;
    f32 velYRange = 20.f;

    if ((gPrevFrameObjectCount > (OBJECT_POOL_CAPACITY - 90)) && numParticles > 10) {
        numParticles = 10;
    }

    if (gPrevFrameObjectCount > (OBJECT_POOL_CAPACITY - 30)) {
        numParticles = 0;
    }

    for (int i = 0; i < numParticles; i++) {
        f32 scale = RandomFloat() * (sizeRange * 0.1f) + sizeBase * 0.1f;
        auto particle = spawn_object(obj, MODEL_MIST, (const BehaviorScript*) 0x130007dc);

        particle->oBehParams2ndByte = 2;
        particle->oMoveAngleYaw = RandomU16();
        particle->oGravity = 2.52f;
        particle->oDragStrength = 1.0f;
        particle->oForwardVel = RandomFloat() * forwardVelRange + forwardVelBase;
        particle->oPosX = obj->oPosX;
        particle->oPosY = obj->oPosY;
        particle->oPosZ = obj->oPosZ;
        particle->oVelX = 0.f;
        particle->oVelY = RandomFloat() * velYRange + velYBase;
        particle->oVelZ = 0.f;

        scale_object(particle, scale);
    }
}
