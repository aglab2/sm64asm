#include "key.h"
extern "C"
{
    #include "audio_defines.h"
    #include "game/object_helpers.h"
    #include "game/object_helpers2.h"
    #include "object_constants.h"
    #include "game/spawn_sound.h"
    #include "engine/math_util.h"
    #include "model_ids.h"
    #include "game/print.h"
}
#include "locked_box.h"

#define oChild OBJECT_FIELD_OBJ(0x1c)

triplet sPositions[] = {
    { 4387, 1120, 714 },
    { 4542, 1241, 714 },
    { 4693, 1120, 714 },
};

void Key::InsideBoo(void)
{
    obj_become_intangible();
    copy_object_pos(this, parentObj);
    if (parentObj->oBooDeathStatus == BOO_DEATH_STATUS_DYING)
    {
        oAction = 1;
        auto angle = gMarioObject->oMoveAngleYaw;
        oVelX = sins(angle) * 3.0f;
        oVelZ = coss(angle) * 3.0f;
        oVelY = 35.0f;
    }
}

void Key::DeadBoo(void)
{
    obj_update_floor_and_walls();
    obj_if_hit_wall_bounce_away();
    if (oMoveFlags & OBJ_MOVE_13)
        PlaySound2(SOUND_GENERAL_COIN_DROP);
    
    if (oTimer > 90 || (oMoveFlags & OBJ_MOVE_LANDED))
        oAction = ACTIVE;

    obj_move_standard(-30);
}

void Key::Active()
{
    auto marioPos = *(triplet*) &gMarioObject->oPosX;
    marioPos.y += 100.f;
    auto dist = marioPos.Distance(oPos);

    if (dist < 100.f)
    {
        PlaySound2(SOUND_MENU_COLLECT_SECRET);
        spawn_object(this, MODEL_SPARKLES, (const BehaviorScript*) 0x13000a14);
        oChild->oAnimState = 1;
        oKeyBox->oLockedBoxKeyLeft--;
        activeFlags = 0;
    }
}

void Key::Init(void)
{
    oChild = spawn_object(this, 0xf2, (BehaviorScript*) 0x13002A48);
    auto val = (oBehParams & 0x00ff0000) >> 16;
    *(triplet*) &oChild->oPosX = sPositions[val];
    oKeyBox = obj_nearest_object_with_behavior((const BehaviorScript*) 0x40800C);
}

void Key::Step(void)
{
    switch (oAction)
    {
        case INSIDE: return InsideBoo();
        case DEAD: return DeadBoo();
        case ACTIVE: return Active();
    }
}

uintptr_t Key::Behavior[] = 
{
    0x23000000, 0x00640040,
    0x102A0010,
    0x11010081,
    0x30000000, 0x001EFE70, 0xFFBA03E8, 0x03E800C8, 0x00000000,
    0x0C000000, 0x802A4120,
    0x0C000000, (uintptr_t) sInit,
    0x08000000,
    0x0C000000, (uintptr_t) sStep,
    0x0F130083,
    0x09000000
};