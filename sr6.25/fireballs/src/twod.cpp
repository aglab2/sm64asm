#include "twod.h"

#include <inputs.h>

struct Config
{
    short Angle;
    short pad1;
    short Zooming;
    short pad2;
};

#define ANGLE_MAX 0x2200
#define ANGLE_MIN 0
#define ANGLE_OFFSET 0x0680

#define CONFIG ((struct Config*) (0x80400020))

static bool ShouldFilter(short angle, short& pressed, short& hold)
{
    if (!(hold & BUTTON_DUP))
        return false;

    if (angle > 0x6000)
        return false;
    if (angle < -0x6000)
        return false;
    
    pressed &= ~(BUTTON_DUP);
    hold &= ~(BUTTON_DUP);

    if (0x1010 > angle || angle > -0x1010)
        return false;

    return true;
}

void TwoD::Init()
{
    CONFIG->Angle = 0x0900;
    CONFIG->Zooming = 0x441B;
}

void TwoD::Step()
{
    ParallelLakituAngle -= bparam12;
    if (bparam3)
        M64_MARIO_STRUCT->pos.z = pos.z;
    else
        M64_MARIO_STRUCT->pos.x = pos.x;
    
    auto hold = M64_CONTROLLER1_BUTTONS_HOLD;
    auto pressed = M64_CONTROLLER1_BUTTONS_PRESS;

    if ((pressed & BUTTON_CUP) && CONFIG->Angle + ANGLE_OFFSET <= ANGLE_MAX)
    {
        CONFIG->Angle += ANGLE_OFFSET;
        CONFIG->Zooming += 0x15;
    }

    if ((pressed & BUTTON_CDOWN) && CONFIG->Zooming - ANGLE_OFFSET >= ANGLE_MIN)
    {
        CONFIG->Angle -= ANGLE_OFFSET;
        CONFIG->Zooming -= 0x15;
    };
    
    hold &= ~(BUTTON_CUP | BUTTON_CDOWN);
    pressed &= ~(BUTTON_CUP | BUTTON_CDOWN);

    short angle = PlayerCamera.rotation - bparam12;
    if (ShouldFilter(angle, pressed, hold))
    {
        if (angle > 0)
        {
            ParallelLakituAngle = 0x2000;
            hold &= ~(BUTTON_DRIGHT | BUTTON_CRIGHT);
            pressed &= ~(BUTTON_DRIGHT | BUTTON_CRIGHT);
        }
        else
        {
            ParallelLakituAngle = -0x2000;
            hold &= ~(BUTTON_DLEFT | BUTTON_CLEFT);
            pressed &= ~(BUTTON_DLEFT | BUTTON_CLEFT);
        }
    }
    else
    {
        if (ParallelLakituAngle >= 0x2000)
        {
            ParallelLakituAngle = 0x2000;
            hold &= ~(BUTTON_DRIGHT | BUTTON_CRIGHT);
            pressed &= ~(BUTTON_DRIGHT | BUTTON_CRIGHT);
        }
        if (ParallelLakituAngle <= -0x2000)
        {
            ParallelLakituAngle = -0x2000;
            hold &= ~(BUTTON_DLEFT | BUTTON_CLEFT);
            pressed &= ~(BUTTON_DLEFT | BUTTON_CLEFT);
        }
    }
    
    M64_CONTROLLER1_BUTTONS_HOLD = hold;
    M64_CONTROLLER1_BUTTONS_PRESS = pressed;

    ParallelLakituState = 4;
    ParallelLakituType = 10;
    ParallelLakituAngle += bparam12;
}

int TwoD::Behavior[] = {
    0x0c000000, (int) sInit,
    0x08000000,
    0x0c000000, (int) sStep,
    0x09000000,
};