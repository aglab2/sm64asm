#include "wall_cucking.h"
extern "C"
{
    #include "game/level_update.h"
    #include "game/object_helpers.h"
    #include "engine/math_util.h"
}

#define SURFACE_YAW(s) (atan2s(((s)->normal.z), ((s)->normal.x)))

static s16 angleToMario(Surface* wall)
{
    return abs_angle_diff(SURFACE_YAW(wall), gMarioState->faceAngle[1]);
}

Surface* getBestWall(WallCollisionData* data)
{
    if (data->numWalls == 0)
        return nullptr;

    Surface* minWall = data->walls[0];
    s32 minWallDYaw = angleToMario(minWall);
    for (int i = 1; i < data->numWalls; i++) {
        Surface* wall = data->walls[i];
        s16 wallDYaw = angleToMario(wall);
        if (wallDYaw > minWallDYaw) {
            minWallDYaw = wallDYaw;
            minWall = wall;
        }
    }

    return minWall;
}
