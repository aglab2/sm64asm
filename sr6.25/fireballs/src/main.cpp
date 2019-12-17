#include "crumbling.h"
#include "fireball.h"
#include "pieces.h"
#include "control.h"
#include "twod.h"

#define REGISTER_BEHAVIOR(list, obj) list, 0x04000000, (int) obj::Behavior,

int _start[] =
{
    REGISTER_BEHAVIOR(0x00090000, Crumbling)     // 409300
    REGISTER_BEHAVIOR(0x00040000, Pieces)        // 40930c
    REGISTER_BEHAVIOR(0x00040000, FireBall)      // 409318
    REGISTER_BEHAVIOR(0x00040000, FireBallTail)  // 409324
    REGISTER_BEHAVIOR(0x00040000, Control)       // 409330
    REGISTER_BEHAVIOR(0x00040000, TwoD)          // 40933c
};