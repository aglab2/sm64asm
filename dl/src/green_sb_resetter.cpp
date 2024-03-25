#include "green_sb_resetter.h"
extern "C"
{
    #include <game/level_update.h>
    #include <game/memory.h>
    #include <game/object_helpers.h>
    #include <game/object_helpers2.h>
    #include <game/spawn_sound.h>
    extern void func_802AA618(s32 count, s32 offsetY, f32 size);
}
#include "puffer.h"

#define spawn_mist_particles_variable func_802AA618
#define cur_obj_scale_over_time func_802A3398

static void resetAllGreenSwitchBlocks()
{
    uintptr_t *behaviorAddr = (uintptr_t *) segmented_to_virtual((const BehaviorScript *) 0x13000CFC);
    struct ObjectNode *listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    struct Object *obj = (struct Object *) listHead->next;
    while (obj != (struct Object *) listHead) {
        if (obj->behavior == behaviorAddr && obj->activeFlags != 0) 
        {
            f32 dx = obj->oPosX - gMarioObject->oPosX;
            f32 dy = obj->oPosY - gMarioObject->oPosY;
            f32 dz = obj->oPosZ - gMarioObject->oPosZ;
            if (dx*dx + dy*dy + dz*dz  < 10000000.f)
                puffAt(obj, 100.f, 10);

            auto gears = obj->prevObj;
            obj->oPosX = gears->oHomeX;
            obj->oPosY = gears->oHomeY;
            obj->oPosZ = gears->oHomeZ;
            obj->oVelX = 0;
            obj->oVelY = 0;
            obj->oVelZ = 0;
            obj->oFaceAnglePitch = 0;
            obj->oAngleVelPitch = 0;
            obj->oForwardVel = 0;
            
            gears->oPosX = gears->oHomeX;
            gears->oPosY = gears->oHomeY;
            gears->oPosZ = gears->oHomeZ;
            gears->oVelX = 0;
            gears->oVelY = 0;
            gears->oVelZ = 0;
            gears->oFaceAnglePitch = 0;
            gears->oAngleVelPitch = 0;
            gears->oForwardVel = 0;
        }

        obj = (struct Object *) obj->header.next;
    }
}

void GreenSwitchBlockResetter::Step()
{
    auto o = gCurrentObject;
    switch (o->oAction) 
    {
        /**
         * Set the switch's model and scale. If Mario is standing near the
         * switch's middle section, transition to the pressed state.
         */
        case PURPLE_SWITCH_IDLE:
            if (gMarioObject->platform == o && !(gMarioStates[0].action & MARIO_UNKNOWN_13)) {
                if (lateral_dist_between_objects(o, gMarioObject) < 127.5f) {
                    o->oAction = PURPLE_SWITCH_PRESSED;
                    resetAllGreenSwitchBlocks();
                    PlaySound2(SOUND_OBJ2_BOWSER_PUZZLE_PIECE_MOVE);
                }
            }
            break;

        /**
         * Collapse the switch downward, play a sound, and shake the screen.
         * Immediately transition to the ticking state.
         */
        case PURPLE_SWITCH_PRESSED:
            cur_obj_scale_over_time(2, 3, 1.f, 0.2f);
            if (o->oTimer == 3) {
                o->oAction = PURPLE_SWITCH_WAIT_FOR_MARIO_TO_GET_OFF;
            }
            break;

        /**
         * Make the switch look unpressed again, and transition back to the
         * idle state.
         */
        case PURPLE_SWITCH_UNPRESSED:
            cur_obj_scale_over_time(2, 3, 0.2f, 1.f);
            if (o->oTimer == 3) {
                o->oAction = PURPLE_SWITCH_IDLE;
            }
            break;

        /**
         * Mario is standing on the switch, but time has expired. Wait for
         * him to get off the switch, and when he does so, transition to the
         * unpressed state.
         */
        case PURPLE_SWITCH_WAIT_FOR_MARIO_TO_GET_OFF:
            if (!obj_is_mario_on_platform()) {
                o->oAction = PURPLE_SWITCH_UNPRESSED;
            }
            break;
    }
}

int GreenSwitchBlockResetter::Behavior[] =
{
    0x11010001,
    0x2A000000, 0x04063570,
    0x08000000,
    0x0c000000, (int) sStep,
    0x0C000000, (int) 0x803839CC, 
    0x09000000,
};

typedef void (*ObjHandler)();
void preGreenSwitchBoard()
{
    bool init = gCurrentObject->oAction == 0;
    ObjHandler handler = (ObjHandler) 0x80600AC0;
    handler();
    if (init)
    {
        auto gears = gCurrentObject->prevObj;
        gears->oHomeX = gears->oPosX;
        gears->oHomeY = gears->oPosY;
        gears->oHomeZ = gears->oPosZ;
    }
}

// 0x3FD0