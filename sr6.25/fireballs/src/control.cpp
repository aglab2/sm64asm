#include "control.h"
#include "fireball.h"

#define oBowser rootObj
#define o2DObject Children[0]
#define o2DObjectState Vars[1]
#define oPrevCollision Vars[0]
#define oCurrentPosition Vars[2]
#define oFireBall Children[1]
#define oKaizoMode Vars[3]

#define MIN_POSITION -20000
#define MAX_POSITION 20000

#define FIREBALL_FLY_TIME 54
#define FIREBALL_CONTROLLED_TIME 70

struct PositionElem
{
    triplet pos;
    int height;
};

enum Axis
{
    X,
    Z,
};

struct TwoDCombo
{
    enum Axis axis;
    float value;
    unsigned short angle;
};

static TwoDCombo sTwoDCombos[] = {
    { X, -4200,  0xC000 },
    { Z, -4200,  0x8000  },
    { X, 4200, 0x4000  },
    { Z, 4200, 0x0000 },
    { X, 0, 0x0000 },
};

static PositionElem sPositionElem1[] =
{
    { { -1791, -6299, 1819 }, MIN_POSITION },
    { { -1773, -3899, -1330 }, -4500 },
    { { -1786, 2400,  180 }, 1380 },
    { { -1786, 4649,  180 }, 4300 },
    { { -1786, 6899,  180 }, 6500 },
    { { 0,0,0 }, MAX_POSITION },
};

static PositionElem sPositionElem2[] =
{
    { { -158, -3600, -1818 }, MIN_POSITION },
    { { -158, -1650, -1818 }, -2300 },
    { { -158, 300, -1818 }, -300 },
    { { 1190, 2250, -1799 }, 1500 },
    { { -1215, 3449, -1796 }, 3500 },
    { { 0,0,0 }, MAX_POSITION },
};

static PositionElem sPositionElem3[] =
{
    { { 1798, -2550, -317 }, MIN_POSITION },
    { { 1798, -750, -317 }, -1700 },
    { { 1798, 1049, -317 }, 1000 },
    { { 1798, 2849, -317 }, 2400 },
    { { 1798, 4500, -317 }, 4500 },
    { { 0,0,0 }, MAX_POSITION },
};

static PositionElem sPositionElem4[] =
{
    { { 169, 150, 1797 }, MIN_POSITION },
    { { -1048, 2250, 1803 }, 1300 },
    { { -447, 4050, 1808 }, 2744 },
    { { 0, 6149, 0 }, 5800 },
    { { 0,0,0 }, MAX_POSITION },
};

struct PositionElem* sPositionElems[] = { sPositionElem1, sPositionElem2, sPositionElem3, sPositionElem4 };

void Control::Set2DState()
{
    auto& combo = sTwoDCombos[o2DObjectState];

    o2DObject->bparam12 = combo.angle;
    o2DObject->bparam3 = combo.axis;
    o2DObject->pos.x = combo.value;
    o2DObject->pos.z = combo.value;

    ParallelLakituAngle = combo.angle;
    oCurrentPosition = 0;
}

void Control::CheckBowserPosition()
{
    PositionElem* elems = sPositionElems[o2DObjectState];

    while (elems[oCurrentPosition + 1].height < M64_MARIO_OBJ_PTR->pos.y) oCurrentPosition++;
    while (elems[oCurrentPosition].height > M64_MARIO_OBJ_PTR->pos.y) oCurrentPosition--;
    
    oBowser->pos = elems[oCurrentPosition].pos;
}

void Control::Init()
{
    oKillBowser = false;
    oKaizoMode = SaveFile_GetTotalStarCount(gCurrSaveFileNum - 1, 0, 24) > 200;
    oBowser = FindObject(0x13001850);
    o2DObject = SpawnObj(this, 0, 0x40933c);
    o2DObjectState = 0;
    Set2DState();
    oPrevCollision = M64_MARIO_STRUCT->curr_collision_triangle->collision_type;
    oCurrentPosition = 0;
    oFireBall = 0;
}

void Control::Check2DCollision()
{
    auto coll = M64_MARIO_STRUCT->curr_collision_triangle->collision_type;

    if (oPrevCollision == 0x1b && coll == 0x1c)
    {
        o2DObjectState++;
        o2DObjectState %= 4;
        Set2DState();
    }
    if (oPrevCollision == 0x1d && coll == 0x1c)
    {
        o2DObjectState--;
        o2DObjectState += 4;
        o2DObjectState %= 4;
        Set2DState();
    }

    oPrevCollision = coll;
}

void Control::SpawnFireBalls()
{
    if (oFireBall)
    {
        if (timer == FIREBALL_FLY_TIME)
        {
           oBowser->action = 0xF;
        }
        if (timer < FIREBALL_CONTROLLED_TIME)
        {
            oFireBall->pos = oBowser->pos;
            auto& combo = sTwoDCombos[o2DObjectState];
            oFireBall->oAxis = 1 - combo.axis;
        }
    }

    int spawnTime = 150 - M64_MARIO_OBJ_PTR->pos.y / 150;
    if (!oKaizoMode)
        spawnTime += 30;

    if (oKillBowser)
        return;
    
    oKillBowser = DistanceFromObject(M64_MARIO_OBJ_PTR, this) < 100;
    if (!oKillBowser && M64_MARIO_OBJ_PTR->pos.y > 5000 && o2DObjectState == 3)
        return;

    if (timer > spawnTime || oKillBowser)
    {
        oBowser->action = 3;
        oFireBall = SpawnObj(this, 248, 0x409318);
        oFireBall->oKillBowser = oKillBowser;
        oFireBall->pos = oBowser->pos;

        timer = 0;
    }
}

void Control::ControlBowser()
{
    if (oBowser->action == 5 || oBowser->action == 6)
    {
        timer = 0;
        return;
    }

    oBowser->faceAngleYaw = oBowser->angleToMario;

    if (oBowser->action != 3 && oBowser->action != 4 && oBowser->action != 0xF)
        oBowser->action = 0x12;
}

void Control::ControlBowserFini()
{
    oBowser->pos.x = 0;
    oBowser->pos.z = 0;
    if (oFireBall && oFireBall->action == FireBall::Actions::EXPLODE)
    {
        oBowser->action = 4;
        o2DObjectState = 4;
        Set2DState();
    }
}

void Control::Step()
{
    ControlBowser();
    if (!oKillBowser)
    {
        Check2DCollision();
        CheckBowserPosition();
        SpawnFireBalls();
    }
    else
    {
        if (timer < 200)
            M64_MARIO_STRUCT->pos = pos;
        
        ControlBowserFini();
    }
}

int Control::Behavior[] =
{
    0x0c000000, (int) sInit,
    0x08000000,
    0x0c000000, (int) sStep,
    0x09000000,
};