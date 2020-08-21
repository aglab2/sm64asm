#include "b3f_ctl.h"
extern "C"
{
    #include "audio_defines.h"
    #include "game/level_update.h"
    #include "game/object_helpers.h"
    #include "game/object_helpers2.h"
    #include "game/print.h"
    #include "game/spawn_sound.h"
    #include "engine/behavior_script.h"
    #include "model_ids.h"
}

#define oBowser   OBJECT_FIELD_OBJ(0x1b)
#define oPlatform OBJECT_FIELD_OBJ(0x1c)
#define oLastCount OBJECT_FIELD_S32(0x1d)
#define oAngle OBJECT_FIELD_S32(0x1d)

static Object* oChildren[8];

enum Actions
{
    INIT,
    TROLL_DEATH,
    AVOIDANCE,
    PH2,
    DEAD,
};

struct Position { float x; float z; };
static Position sSwitchPositions[] = {
    { 0, -900 }, 
    { 0, 900 }, 
    { -900, 0 }, 
    {  900, 0 }, 
};

void B3FCtl::Init()
{
    float d;
    oBowser = obj_find_nearest_object_with_behavior((const BehaviorScript*) 0x13001850, &d);
    oPlatform = obj_find_nearest_object_with_behavior((const BehaviorScript*) 0x408150, &d);

    for (int i = 0; i < 4; i++)
    {
        oChildren[i] = spawn_object(this, 207, (const BehaviorScript*) 0x408168);
        auto& positions = sSwitchPositions[i];
        oChildren[i]->oPosX = positions.x;
        oChildren[i]->oPosY = oPosY;
        oChildren[i]->oPosZ = positions.z;
    }
}

void B3FCtl::Step()
{
    oBowser->oHomeY = oBowser->oPosY;
    oBowser->oPosX = oPosX;
    oBowser->oPosZ = oPosZ;
    if (oBowser->oAction != 5 && oBowser->oAction != 6)
    {
        oBowser->oFaceAngleYaw = angle_to_object(oBowser, gMarioObject);
    }

    if (oAction != DEAD)
    {
        constexpr float minDist = 300.f;
        auto x = gMarioStates->pos[0];
        auto z = gMarioStates->pos[2];
        auto marioDist = x * x + z * z;
        if (marioDist < minDist * minDist)
        {
            x /= sqrtf(marioDist);
            z /= sqrtf(marioDist);
            x *= minDist;
            z *= minDist;
            gMarioStates->pos[0] = x;
            gMarioStates->pos[2] = z;
        }
    }

    switch (oAction)
    {
        case INIT:
            return Phase1();
        case TROLL_DEATH:
            return TrollDeath();
        case AVOIDANCE:
            return Avoidance();
        case PH2:
            return Phase2();
    }
}

void B3FCtl::Phase1()
{
    if (oBowser->oAction != 5 && oBowser->oAction != 6)
    {
        oBowser->oAction = 3;
    }

    int cnt = 0;
    for (int i = 0; i < 4; i++)
        cnt += oChildren[i]->oAction;

    if (cnt != oLastCount && cnt != 4)
    {
        oLastCount = cnt;
        short initAngle = RandomFloat() * 0x800;
        for (int i = 0; i < 32; i++)
        {
            auto flame = spawn_object(this, 144, (const BehaviorScript*) 0x408174);
            flame->oForwardVel = 50.f;
            flame->oMoveAngleYaw = initAngle + 0x800 * i;
        }
    }

    if (4 == cnt)
    {
        oBowser->oPosY = oPosY + 40.f;
        oBowser->oAction = 4;
        oAction = TROLL_DEATH;
    }
}

void B3FCtl::TrollDeath()
{ 
    if (oBowser->oPosY < oPosY)
    {
        {
            constexpr float minDist = 1200.f;
            auto x = gMarioStates->pos[0];
            auto z = gMarioStates->pos[2];
            auto marioDist = x * x + z * z;
            if (marioDist > minDist * minDist)
            {
                x /= sqrtf(marioDist);
                z /= sqrtf(marioDist);
                x *= minDist;
                z *= minDist;
                gMarioStates->pos[0] = x;
                gMarioStates->pos[2] = z;
            }
        }

        oAction = AVOIDANCE;
        oPosY = 2012.f;
        oPlatform->activeFlags = 0;
        for (int i = 0; i < 4; i++)
            oChildren[i]->oPosY = 2012.f;

        oAngle = RandomFloat() * 0x10000;
        spawn_object(this, MODEL_BOWSER_FLAMES, (const BehaviorScript*) 0x1300381c);
        create_sound_spawner(SOUND_GENERAL_BOWSER_BOMB_EXPLOSION);
        ShakeScreen(3);
    }
}

void B3FCtl::Avoidance()
{
    if (50 < oTimer)
    {
        oBowser->oAction = 3;
    }

    if (150 < oTimer)
    {
        if (oTimer < 480)
        {
            oAngle += 977;

            if ((oTimer % 5) == 1 || (oTimer % 5) == 2)
            {
                auto flame = spawn_object(this, 144, (const BehaviorScript*) 0x408174);
                flame->oForwardVel = 18.f;
                flame->oMoveAngleYaw = oAngle;
            }
            
            if (oTimer % 7 == 0)
            {
                auto flame = spawn_object(this, 144, (const BehaviorScript*) 0x408174);
                flame->oForwardVel = 10.f;
                flame->oMoveAngleYaw = -oAngle * 2;
            }
        }
    }

    if (oTimer == 600)
    {
        oAction = PH2;
        for (int i = 0; i < 4; i++)
        {
            oChildren[i]->oAction = 0;
            scale_object_xyz(oChildren[i], 1.5f, 1.5f, 1.5f);
        }
    }
}

void B3FCtl::Phase2()
{
    oBowser->oAction = 3;

    if ((oTimer % 30) == 0)
    {
        short initAngle = RandomFloat() * 0x10000;
        for (int i = 0; i < 7; i++)
        {
            auto flame = spawn_object(this, 144, (const BehaviorScript*) 0x408174);
            flame->oForwardVel = 23.f;
            flame->oMoveAngleYaw = initAngle + 0x10000 / 7 * i;
        }
    }
    
    int cnt = 0;
    for (int i = 0; i < 4; i++)
        cnt += oChildren[i]->oAction;

    if (4 == cnt)
    {
        oBowser->oPosY = oPosY + 40.f;
        oBowser->oAction = 4;
        oAction = DEAD;
    }
}

uintptr_t B3FCtl::Behavior[] = 
{
    0x0c000000, (uintptr_t) sInit,
    0x08000000,
    0x0c000000, (uintptr_t) sStep,
    0x09000000,
};