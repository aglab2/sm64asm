#include "bully_lava_death.h"

extern "C"
{
    #include <audio_defines.h>
    #include <game/area.h>
    #include <game/ingame_menu.h>
    #include <game/object_helpers.h>
    #include <game/object_list_processor.h>
    #include <game/spawn_sound.h>
    #include <engine/behavior_script.h>
    #include <engine/graph_node.h>
    #include <engine/math_util.h>
    #include <model_ids.h>
}
#include <object_fields.h>

static bool gBullyKilled = false;
static bool gBlockSpawnAnimation = false;

s8 objLavaDeathBullyThreeBullies(void) {
    struct Object* o = gCurrentObject;
    struct Object *deathSmoke;

    if (o->oTimer >= 31) {
        obj_disable();
        o->oAction = 200;
        return TRUE;
    } else {
        // Sinking effect
        o->oPosY -= 10.0f;
    }

    if ((o->oTimer % 8) == 0) {
        PlaySound2(SOUND_OBJ_BULLY_EXPLODE_2);
        deathSmoke = spawn_object(o, MODEL_SMOKE, (const BehaviorScript*) 0x13003558);
        deathSmoke->oPosX += RandomFloat() * 20.0f;
        deathSmoke->oPosY += RandomFloat() * 20.0f;
        deathSmoke->oPosZ += RandomFloat() * 20.0f;
        deathSmoke->oForwardVel = RandomFloat() * 10.0f;
    }

    return FALSE;
}

s8 objLavaDeathBullySingleBully(void) {
    struct Object* o = gCurrentObject;
    struct Object *deathSmoke;

    if (gBullyKilled)
    {
        o->oPosY = -10000.f;
        o->oAction = 200;
        obj_disable();
        return TRUE;
    }

    if (o->oTimer >= 31) {
        if (o->oBehParams2ndByte == BULLY_BP_SIZE_SMALL)
        {
            o->activeFlags = 0;
        }
        else
        {
            gBullyKilled = true;
            o->oAction = 200;
            obj_disable();
        }
        return TRUE;
    } else {
        // Sinking effect
        o->oPosY -= 10.0f;
    }

    if ((o->oTimer % 8) == 0) {
        PlaySound2(SOUND_OBJ_BULLY_EXPLODE_2);
        deathSmoke = spawn_object(o, MODEL_SMOKE, (const BehaviorScript*) 0x13003558);
        deathSmoke->oPosX += RandomFloat() * 20.0f;
        deathSmoke->oPosY += RandomFloat() * 20.0f;
        deathSmoke->oPosZ += RandomFloat() * 20.0f;
        deathSmoke->oForwardVel = RandomFloat() * 10.0f;
    }

    return FALSE;
}

bool preStarSpawnInit(void)
{
    struct Object* o = gCurrentObject;
    o->oMoveAngleYaw = atan2s(o->oHomeZ - o->oPosZ, o->oHomeX - o->oPosX);
    if (gBlockSpawnAnimation)
    {
        o->oAction = 3;
        o->oPosX = o->oHomeX;
        o->oPosY = o->oHomeY;
        o->oPosZ = o->oHomeZ;
        return false;
    }
    else
    {
        return true;
    }
}

void redCoinStarSpawnInit(void)
{
    struct Object* o = gCurrentObject;
    gRedCoinsCollected = o->oHiddenStarTriggerCounter;
    o->oSpinyTargetYaw++;
    gBlockSpawnAnimation = o->oSpinyTargetYaw < 6;
}

void ResetDeathFlags::Init()
{
    if (0 == gCurrCourseNum)
    {
        gBullyKilled = false;
        activeFlags = 0;
    }
    else
    {
        gBlockSpawnAnimation = true;
        if (gBullyKilled)
        {
            f32 d;
            if (struct Object* bully = obj_find_nearest_object_with_behavior((const BehaviorScript*) 0x13003660, &d))
            {
                bully->oAction = 100;
            }
        }
    }
}

void ResetDeathFlags::Step()
{
    gBlockSpawnAnimation = oTimer < 5;
}

int ResetDeathFlags::Behavior[] =
{
    0x0c000000, (int) sInit,
    0x08000000,
    0x0c000000, (int) sStep,
    0x09000000,
};
