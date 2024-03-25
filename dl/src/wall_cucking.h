#pragma once

#include "types.h"
extern "C"
{
    #include <engine/surface_collision.h>
}

struct Surface* getBestWall(WallCollisionData*);
