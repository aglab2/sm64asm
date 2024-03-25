#include "blue_star_block.h"
extern "C"
{
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
    if (gMarioStates->numStars < 150)
        gCurrentObject->activeFlags = 0;
}

void BlueStarBlock::Step()
{
    auto o = gCurrentObject;
    if (gMarioStates->numStars >= 333)
    {
        if (gPlayer1Controller->buttonPressed & L_TRIG)
        {
            if (gCurrentObject->oDistanceToMario < 1000.f)
                spawn_mist_particles_variable(0, 0, 100.f);

            if (o->header.gfx.node.flags & GRAPH_RENDER_INVISIBLE)
            {
                o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
            }
            else
            {
                o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
            }
        }
    }

    if (!(o->header.gfx.node.flags & GRAPH_RENDER_INVISIBLE))
        load_object_collision_model();
}

int BlueStarBlock::Behavior[] =
{
    0x11010041,
    0x0c000000, (int) sInit,
    0x2A000000, 0x4086270,
    0x08000000,
    0x0c000000, (int) sStep,
    0x09000000,
};
