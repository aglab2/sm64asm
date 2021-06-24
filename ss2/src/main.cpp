#include "ctl.h"
#include "qs_rotat.h"
#include "water_rotat.h"

#define REGISTER_BEHAVIOR(list, obj) list, 0x04000000, (int) obj::Behavior,

int _start[] = {
    REGISTER_BEHAVIOR(0x00060000, Ctl) // 408000
    REGISTER_BEHAVIOR(0x00090000, QSRotat) // 40800C
    REGISTER_BEHAVIOR(0x00090000, WaterRotat) // 408018
};
