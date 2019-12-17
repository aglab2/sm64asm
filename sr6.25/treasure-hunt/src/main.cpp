#include "treasure_hunt.h"

#define REGISTER_BEHAVIOR(list, obj) list, 0x04000000, (int) obj::Behavior,

int _start[] =
{
    REGISTER_BEHAVIOR(0x00040000, TreasureHunt)
    (int) TreasureHunt::Draw,
};