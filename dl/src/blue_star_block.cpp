#include "blue_star_block.h"
#include "blue_star_mode.h"
extern "C"
{
    #include <game/display.h>
    #include <game/game.h>
    #include <game/level_update.h>
    #include <game/object_helpers.h>
    #include <game/object_helpers2.h>
    #include <engine/graph_node.h>
    #include <engine/surface_load.h>
    extern void func_802AA618(s32 count, s32 offsetY, f32 size);
}

#define spawn_mist_particles_variable func_802AA618

void BlueStarBlock::Init()
{
    if (!blue_star_mode_enabled())
        gCurrentObject->activeFlags = 0;
}

void BlueStarBlock::Step()
{
    load_object_collision_model();
}

int BlueStarBlock::Behavior[] =
{
    0x11010041,
    0x0c000000, (int) sInit,
    0x2A000000, 0x4086270,
    0x08000000,
    0x0c000000, (int) 0x803839cc,
    0x09000000,
};
