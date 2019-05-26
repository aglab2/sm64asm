#include "MovingSpike.h"

#include <inputs.h>

enum States
{
    STANDING = 0,
    MOVING,
};

enum Direction
{
    X = 1,
    Y = 2,
    Z = 4,
    ROTATING_X = 8,
    ROTATING_Y = 16,
    REVERSE = 32,
};

void MovingSpike::Init()
{
    posInit = pos;
    if (bparam2 == 0)
        return;

    movementSpeed = (float) bparam34 / (float) bparam2;

    if (bparam1 & REVERSE)
        movementSpeed = -movementSpeed;
}

void MovingSpike::Step()
{
    enum States state = static_cast<States>(action);
    switch (state)
    {
        case STANDING:
        {
            if (M64_CONTROLLER1_BUTTONS_PRESS & BUTTON_A)
            {
                if (bparam1 & (X | Y | Z))
                    movementSpeed = -movementSpeed;

                action = MOVING;
            }
        }
        break;
        case MOVING:
        {
            
            if (timer == bparam2)
            {
                action = STANDING;
                return;
            }

            if (bparam1 & X)
                pos.x += movementSpeed;
            if (bparam1 & Y)
                pos.y += movementSpeed;
            if (bparam1 & Z)
                pos.z += movementSpeed;
            if (bparam1 & ROTATING_X)
                z_rotation2 += movementSpeed;
            if (bparam1 & ROTATING_Y)
                y_rotation += movementSpeed;

        }
        break;
    }
    // fill me
}

// bparam1 direction mask
// bparam2 frames to mov
// bparam34 distance
int MovingSpike::Behavior[] =
{
    0x11010009,
    0x2A000000, 0x04035E00,
    0x0E431000,
    0x0C000000, (int) sInit,
    0x08000000,
    0x0C000000, (int) sStep,
    0x0C000000, (int) 0x803839CC,
    0x09000000,    
};