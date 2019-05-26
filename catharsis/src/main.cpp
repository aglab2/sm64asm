#include "empty.h"
#include "WaterAlterer.h"
#include "MovingSpike.h"
#include "SaveState.h"
#include "DeathFloor.h"

#define REGISTER_BEHAVIOR(list, obj) { list, 0x04000000, (int) obj::Behavior },

int _start[][3] = {
    REGISTER_BEHAVIOR(0x00040000, EmptyObject)  // 408000
    REGISTER_BEHAVIOR(0x00040000, WaterAlterer) // 40800C
    REGISTER_BEHAVIOR(0x00090000, MovingSpike)  // 408018
    REGISTER_BEHAVIOR(0x00040000, SaveState)    // 408024
    REGISTER_BEHAVIOR(0x00040000, DeathFloor)   // 408030
};