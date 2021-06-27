extern "C"
{
    #include "game/object_helpers.h"
    #include "game/object_helpers2.h"
    #include "engine/surface_load.h"
}
#include "object_fields.h"
#include "v_switch.h"

void vanishInit(Object* o)
{
    o->oHiddenObjectUnkF4 = obj_nearest_object_with_behavior((const BehaviorScript*) 0x408054);
}

void vanishStep(Object* o)
{
    o->oTimer = o->oHiddenObjectUnkF4->oVSwitchTimer;
    if (o->oHiddenObjectUnkF4->oAction == 2 /*PURPLE_SWITCH_TICKING*/ && o->oTimer < 200)
    {
        obj_enable_rendering();
        obj_unhide();
        obj_become_tangible();
        load_object_collision_model();
        obj_wait_then_blink(160, 20);
    }
    else
    {
        obj_disable_rendering();
        obj_become_intangible();
    }
}
