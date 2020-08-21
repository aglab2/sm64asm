#include "control.h"

#include <inputs.h>

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

static triplet sPositions1[] = {
    { 1094, 307, -4427 },
    { -1860, 690, 2199 },
    { -4177, -281, 6833 },
};

static triplet sPositions2[] = {
    { -8892, -7008, -15438 },
    { -3881, -6743, -11162 },
    { -4592, -4133, -11107 },
    { -4074, -5105, -9080 },
};

static triplet sPositions3[] = {
    { 0, 0, 0 },
    { -50, 822, 3609 },
    { -641, 3492, 7157 },
    { -1549, 1603, 8314 },
};

static triplet sPositions4[] = {
    { 9904, 144, -11945 },
    { 11054, 420, -13278 },
    { 7742, 1298, -12597 },
    { 7497, 3548, -6691 },
    { 7497, 2142, -6541 },
};

static triplet sPositions5[] = {
    { -2004, 701, 1930 },
    { 2756, 440, -4946 },
    { 2319, 440, -6733 },
    { 540, -4240, -1985 },
    { 606, -6432, -2930 },
};

static triplet sPositions6[] = {
    { 2239, -309, -3389 },
    { 1740, 351, -5198 },
    { 5170, 2571, -667 },
    { 5816, 2289, -6647 },
};

static triplet sPositions7[] = {
    { -3332, -1014, -4465 },
    { 3602, 625, 407 },
    { 3215, 1979, 2246 },
};

static triplet sPositions8[] = {
    { 3309, -2254, 9213 },
    { -368, -1651, 9007 },
    { 245, 750, -7535 },
};

static triplet sPositions9[] = {
    { 2171, -2807, 2957 },
    { 1977, -1637, -4143 },
    { -2328, -1615, -3858 },
};

static triplet sPositions10[] = {
    { -10, 136, -981 }, 
    { -50, 1500, -8915 }, 
    { -3433, 4110, -10200 },
};

static struct triplet sPositions11[] = {
    { -7004, -1010, -1633 },
    { 3290, 609, -2097 },
    { -58, 1637, -3538 },
};

static struct triplet sPositions12[] = {
    { -785, -3884, 6010},
    { -3975, -3553, 2685 },
    { 4673, -996, 1827 },
    { -803, 105, 6167 },
};

static struct triplet sPositions13[] = {
    { -4319, 513, -11539 },
    { 2044, -742, -12969 },
    { 2044, 2078, -13251 },
    { -395, 2795, -15612 },
};

static struct triplet sPositions14[] = {
    { 13795, -1594, -2502 },
    { 7360, -2435, 3406 },
    { -716, -1656, 3740 },
};

static struct triplet sPositions15[] = {
    { 40, 740, 0 },
    { -4075, 0, -1485 },
    { -6755, 779, 1605 },
    { -5979, 3718, 5362 },
};


struct TripletsVector
{
    struct triplet* positions;
    int size;
};

#define POSITIONS_ARRAY_TO_VECTOR(x) { x, ARRAY_SIZE(x) }
static TripletsVector sPositions[] = {
    {},
    POSITIONS_ARRAY_TO_VECTOR(sPositions1),
    POSITIONS_ARRAY_TO_VECTOR(sPositions2),
    POSITIONS_ARRAY_TO_VECTOR(sPositions3),
    POSITIONS_ARRAY_TO_VECTOR(sPositions4),
    POSITIONS_ARRAY_TO_VECTOR(sPositions5),
    POSITIONS_ARRAY_TO_VECTOR(sPositions6),
    POSITIONS_ARRAY_TO_VECTOR(sPositions7),
    POSITIONS_ARRAY_TO_VECTOR(sPositions8),
    POSITIONS_ARRAY_TO_VECTOR(sPositions9),
    POSITIONS_ARRAY_TO_VECTOR(sPositions10),
    POSITIONS_ARRAY_TO_VECTOR(sPositions11),
    POSITIONS_ARRAY_TO_VECTOR(sPositions12),
    POSITIONS_ARRAY_TO_VECTOR(sPositions13),
    POSITIONS_ARRAY_TO_VECTOR(sPositions14),
    POSITIONS_ARRAY_TO_VECTOR(sPositions15),
};

static unsigned char sBrightness = 0x60;

void Control::Init()
{
    auto& vec = sPositions[gCurrCourseNum];
    
    auto positions = vec.positions;
    auto len = vec.size;

    for (int i = 0; i < len - 1; i++)
    {
        auto part = SpawnObj(this, 0xF8, 0x40900C);
        part->pos = positions[i];
        part->posInit = positions[i + 1];
    }
}

void Control::Step()
{
    F2Scroll(0x040369D8, 3, 3);
    
    if ((M64_CONTROLLER1_BUTTONS_PRESS & BUTTON_DUP) && sBrightness != 0xc0)
    {
        sBrightness += 0x20;
    }
    if ((M64_CONTROLLER1_BUTTONS_PRESS & BUTTON_DDOWN) && sBrightness != 0x0)
    {
        sBrightness -= 0x20;
    }

    auto pTrans = (unsigned char*) SegmentedToVirtual(0x04036997);
    *pTrans = sBrightness;
}

int Control::Behavior[] = {
    0x0c000000, (int) sInit,
    0x08000000,
    0x0c000000, (int) sStep,
    0x09000000,
};
