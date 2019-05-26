#include "DeathFloor.h"

const int JumpCollision = 0x29;
const int DeathCollision = 0x7B;

void DeathFloor::Init()
{
    // fill me
}

void DeathFloor::Step()
{
    if ((SM64Health & 0xFF00) == 0x0)
        return;

    Mario* mario = M64_MARIO_STRUCT;
    CollisionTriangle* tri = mario->curr_collision_triangle;

    if (tri->collision_type == JumpCollision && mario->ground_y == mario->pos.y)
    {
        mario->action = 0x03000880;
        mario->speed.y = 10.0;
    }

    if (tri->collision_type == DeathCollision)
    {
        SM64Health -= 0x40;
    }
    else
    {
        if (SM64Health < 0x0880)
            SM64Health += 0x80;
    }
}

int DeathFloor::Behavior[] =
{
    0x0C000000, (int) sInit,
    0x08000000,
    0x0C000000, (int) sStep,
    0x09000000,    
};