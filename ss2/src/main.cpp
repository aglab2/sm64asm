#include "ctl.h"
#include "qs_rotat.h"
#include "water_rotat.h"
#include "moving.h"
#include "propeller.h"
#include "wind_particles.h"
#include "wind_ctl.h"
#include "v_switch.h"
#include "v_platform.h"
#include "v_wk.h"
#include "v_gate.h"
#include "secret.h"
#include "scroll.h"
#include "cap.h"
#include "block.h"
#include "arrow_point.h"
#include "arrow_hour.h"
#include "arrow_minute.h"
#include "bottle.h"

#define REGISTER_BEHAVIOR(list, obj) list, 0x04000000, (int) obj::Behavior,

int _start[] = {
    REGISTER_BEHAVIOR(0x00060000, Ctl)           // 408000
    REGISTER_BEHAVIOR(0x00090000, QSRotat)       // 40800C
    REGISTER_BEHAVIOR(0x00090000, WaterRotat)    // 408018
    REGISTER_BEHAVIOR(0x00090000, Moving)        // 408024
    REGISTER_BEHAVIOR(0x00060000, Propeller)     // 408030
    REGISTER_BEHAVIOR(0x000C0000, WindParticles) // 40803C
    REGISTER_BEHAVIOR(0x00060000, WindCtl)       // 408048
    REGISTER_BEHAVIOR(0x00090000, VSwitch)       // 408054
    REGISTER_BEHAVIOR(0x00090000, VWk)           // 408060
    REGISTER_BEHAVIOR(0x00090000, VPlatform)     // 40806C
    REGISTER_BEHAVIOR(0x00090000, VGate)         // 408078
    (int) onSecretStep,                          // 408084
    (int) onScrollStep,                          // 408088
    (int) onCapStep,                             // 40808C
    REGISTER_BEHAVIOR(0x00090000, Block)         // 408090
    REGISTER_BEHAVIOR(0x00060000, ArrowPoint)    // 40809C
    REGISTER_BEHAVIOR(0x00060000, ArrowHour)     // 4080A8
    REGISTER_BEHAVIOR(0x00060000, ArrowMinute)   // 4080B4
    REGISTER_BEHAVIOR(0x00060000, Bottle)        // 4080C0
};
