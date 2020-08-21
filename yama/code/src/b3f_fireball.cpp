#include "b3f_fireball.h"
extern "C"
{
    #include "game/interaction.h"
    #include "game/object_helpers.h"
    #include "game/object_helpers2.h"
}

void B3FFireball::Init()
{
    oVelY = -28.0f;
    oPosY += 10.f;
    oFlameUnkF4 = 3.f;
}

struct ObjectHitbox sBowserFlameHitbox = {
    /* interactType: */ INTERACT_FLAME,
    /* downOffset: */ 0,
    /* damageOrCoinValue: */ 1,
    /* health: */ 0,
    /* numLootCoins: */ 0,
    /* radius: */ 10,
    /* height: */ 40,
    /* hurtboxRadius: */ 0,
    /* hurtboxHeight: */ 0,
};

void B3FFireball::Step()
{
    obj_scale(oFlameUnkF4);
    set_object_hitbox(this, &sBowserFlameHitbox);
    oBounce = -1.f;
    obj_update_floor_and_walls();
    obj_move_standard(78);
    oInteractStatus = 0;

    auto dist = oPosX * oPosX + oPosZ * oPosZ;
    if (dist > 1560.f * 1560.f)
        activeFlags = 0; 
}

uintptr_t B3FFireball::Behavior[] = 
{
    0x11010001,
    0x2F000000, 0x00040000,
    // 0x0E15001E,
    0x30000000, 0x0000FE70, 0xFFBA03E8, 0x000000C8, 0x00000000,
    0x21000000,
    0x0c000000, (uintptr_t) sInit,
    0x08000000,
    0x0c000000, (uintptr_t) sStep,
    0x0F1A0001,
    0x09000000,
};