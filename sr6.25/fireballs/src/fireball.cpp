#include "fireball.h"

#define oKaizoMode transparency

#define FIREBALL_SPEED 30.0f
#define ROCK_SCALE 0.9f

// The whole startup period takes 100 frames
#define FIREBALL_GROWING_TIME 20
#define FIREBALL_WAITING_TIME 61

#define FIREBALL_ACCELERATING_TIME 10

#define oAccelRate posInit
#define FIREBALL_ACCEL_SPEED (FIREBALL_SPEED / (float)FIREBALL_ACCELERATING_TIME)

#define FIREBALL_ALIVE_TIME 300

#define EXPLODE_TIME 5
#define EXPLODE_DRAINED 40

#define FIREBALL_COLLISION_DISTANCE 700.0f

#define SCALE_DELIMITER 2.0f

void FireBall::Init()
{
    oKaizoMode = SaveFile_GetTotalStarCount(gCurrSaveFileNum - 1, 0, 24) > 200;
}

void FireBall::Growing()
{
    float rockScale = ROCK_SCALE;
    if (!oKaizoMode)
        rockScale /= SCALE_DELIMITER;

    ScaleObject((float) timer / (float) FIREBALL_GROWING_TIME * rockScale);

    if (timer == FIREBALL_GROWING_TIME)
        action = WAITING;
}

void FireBall::Waiting()
{
    if (timer == FIREBALL_WAITING_TIME)
        action = ACCELERATING;
}

void FireBall::Accelerating()
{
    if (timer == 0)
    {
        auto mario = M64_MARIO_STRUCT;

        float x = pos.x - mario->pos.x;
        float y = pos.y - mario->pos.y;
        float z = pos.z - mario->pos.z;

        if (mario->action != 0x08100340)
        {
            if (oAxis == 0)
            {
                x -= mario->speed.x * 42;
            }
            if (oAxis == 1)
            {
                z -= mario->speed.z * 42;
            }
        }

        float plain = sqrtf(x*x + z*z);

        rootObj = SpawnObj(this, 0xF7, 0x409324);
    
        rootObj->faceAnglePitch = -atan2s(plain, y);
        rootObj->faceAngleYaw   =  atan2s(z, x);

        float modifier = -sqrtf(x*x + y*y + z*z) / FIREBALL_ACCEL_SPEED;
        oAccelRate = { x / modifier, y / modifier, z / modifier };
        speed = {};
        rootObj->speed = speed;

        if (oKillBowser)
            rootObj->subaction = 1;
    }

    if (timer == FIREBALL_ACCELERATING_TIME)
    {
        action = FLYING;
    }
    
    speed.x += oAccelRate.x;
    speed.y += oAccelRate.y;
    speed.z += oAccelRate.z;
    
    ObjMoveUsingVel();
    rootObj->pos = pos;
}

void FireBall::Flying()
{
    ObjMoveUsingVel();
    rootObj->pos = pos;
    
    if (oKillBowser)
    {
        if (pos.z > 3500)
            action = GO_BACK;
    }
    else
    {
        if (timer == FIREBALL_ALIVE_TIME)
            active = 0;

        auto mario = M64_MARIO_OBJ_PTR;
        auto dist = DistanceFromObject(mario, this); 

        float collDist = FIREBALL_COLLISION_DISTANCE;
        if (!oKaizoMode)
            collDist /= SCALE_DELIMITER;

        if (dist < collDist)
            action = EXPLODE;
    }
}

void FireBall::Explode()
{
    float rockScale = ROCK_SCALE;
    if (!oKaizoMode)
        rockScale /= SCALE_DELIMITER;

    if (timer <= EXPLODE_TIME)
        ScaleObject(rockScale * (1.0f - (float) timer / (float) EXPLODE_TIME));
    
    if (timer == 0)
    {
        PlaySoundProperly(0x312f0081);
        SpawnObj(this, 0x67, 0x13003840);
        rootObj->subaction = 1;
        
        if (!oKillBowser)
            DropAndSetMarioAction(M64_MARIO_STRUCT, 0x010208B7, 4); // 
    }

    if (!oKillBowser)
    {
        SM64Health -= 0x10;
        if (oKaizoMode)
            SM64Health -= 0x10;
    }
    
    if (timer == EXPLODE_DRAINED)
    {
        active = 0;
    }
}

void FireBall::GoBack()
{
    if (timer == 0)
    {
        rootObj->subaction = 1;
        speed.x = 0;
        speed.y = 0;
        speed.z = -30.0f;
    }

    ObjMoveUsingVel();
    rootObj->pos = pos;

    if (pos.z < 200)
        action = EXPLODE;
}

void FireBall::Step()
{
    faceAnglePitch += 0x69;
    faceAngleRoll  += 0x72;

    switch (action)
    {
        case GROWING: Growing(); break;
        case WAITING: Waiting(); break;
        case ACCELERATING: Accelerating(); break;
        case FLYING: Flying(); break;
        case EXPLODE: Explode(); break;
        case GO_BACK: GoBack(); break;
    }
}

int FireBall::Behavior[] =
{
    0x11010001,
    0x0c000000, (int) sInit,
    0x08000000,
    0x0c000000, (int) sStep,
    0x09000000,
};

struct Vertex
{
    short X;
    short Y;
    short Z;
    short pad;
    short U;
    short V;
    char R;
    char G;
    char B;
    char A;
};

extern "C" void* memset(void* ptr, int value, int num)
{
    char* buf = (char*) ptr;
    for (int i = 0; i < num; i++)
        buf[i] = value;

    return buf;
}

static void Alter(Vertex* v, short offX, short offY, short offZ)
{
    v->X += offX;
    v->Y += offY;
    v->Z += offZ;
}

char randoms[] = {
    9, -1, 6, -8, 3, -2, 7, 6, -6, -4, -7, 4, -6, 1, -6, 3, -6, 0, 
    -4, 1, 7, 5, 0, 7, 9, -7, -2, 1, -10, 0, 2, 6, 5, -5, -4, 5, 6, 
    -7, -8, 8, 3, 1, -4, 2, -2, -9, -10, -2, -5, 5, 3, 9, 7, 6, 5, 3, 
    -8, 2, 2, 4, -6, -6, 9, 4, -6, -9, 1, -3, 3, -5, -9, 6, 8, 7, -4, 
    -3, -9, 5, -4, -3, 3, 1, 0, -2, -10, -5, -10, -9, 7, -1, -8, -7, 
    3, 5, 8, 7, 8, 5, 6, 3,
};

template<int Count>
void FireBallTail::ShakeVertices(int segFrom)
{
    bparam1++; bparam1 %= 100;
    bparam2++; bparam2 %= 100;
    bparam3++; bparam3 %= 100;

    char wasAltered[Count] = {};

    Vertex* vertices = (Vertex*) SegmentedToVirtual(segFrom);
    for (int i = 0; i < Count; i++)
    {
        if (wasAltered[i])
            continue;
        wasAltered[i] = true;

        Vertex* baseVertex = &vertices[i];
        short offX = randoms[bparam1];
        short offY = randoms[bparam2];
        short offZ = randoms[bparam3];

        for (int j = i + 1; j < Count; j++)
        {
            if (wasAltered[j])
                continue;

            Vertex* sameVertex = &vertices[j];
            if (sameVertex->X == baseVertex->X 
             && sameVertex->Y == baseVertex->Y 
             && sameVertex->Z == baseVertex->Z)
             {
                Alter(sameVertex, offX, offY, offZ);
                wasAltered[j] = true;
             }
        }
        Alter(baseVertex, offX, offY, offZ);
    }
}

void FireBallTail::Init() 
{
    oKaizoMode = SaveFile_GetTotalStarCount(gCurrSaveFileNum - 1, 0, 24) > 200;
}

void FireBallTail::Step()
{
    if (subaction == 1)
        HideObject();

    if (timer < FIREBALL_ACCELERATING_TIME)
    {
        float scale = (float) FIREBALL_ACCELERATING_TIME;
        if (!oKaizoMode)
            scale *= SCALE_DELIMITER;

        ScaleObject((float) timer / scale);
    }

    if (timer == FIREBALL_ALIVE_TIME)
        active = 0;

    F2Scroll(0x0405AEE8, 1, 2);
    ShakeVertices<0x44>(0x0405AA20);
}

int FireBallTail::Behavior[] =
{
    0x11010001,
    0x0c000000, (int) sInit,
    0x08000000,
    0x0c000000, (int) sStep,
    0x09000000,
};