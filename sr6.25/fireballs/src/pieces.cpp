#include "pieces.h"

#define ALIVE_TIME 200
#define DEAD_TIME 250
#define DECAY_TIME (DEAD_TIME - ALIVE_TIME)

void Pieces::Step()
{
    if (pos.y < -10000.0f)
    {
        active = 0;
    }

    speed.y -= 3.0f;
    ObjRotateFaceAngleUsingVel();
    ObjMoveUsingVel();
}
    
int Pieces::Behavior[] = {
    0x11010001,
    0x08000000,
    0x0c000000, (int) sStep,
    0x09000000,
};