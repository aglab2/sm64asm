#include "aglab_pillar.h"
#include "aglab_shooting.h"
#include "aglab_camera.h"
#include "ow_despawn.h"

#define REGISTER_BEHAVIOR(list, obj) list, 0x04000000, (int) obj::Behavior,

int _start[] = {
    REGISTER_BEHAVIOR(0x00090000, AglabPillar)          // 408000
    REGISTER_BEHAVIOR(0x00040000, AglabShooting)        // 40800C
    REGISTER_BEHAVIOR(0x00040000, OWDespawn)            // 408018
    REGISTER_BEHAVIOR(0x00040000, AglabCamera)          // 408024
};