#include "two_d.h"
extern "C"
{
    #include "PR/os_cont.h"
    #include "game/game.h"
    #include "game/level_update.h"
    #include "game/camera.h"

    extern s16 sSelectionFlags;
}

struct Config
{
    short Angle;
    short Zooming;
};

#define CONFIG ((struct Config*)&OBJECT_FIELD_OBJ(0x1b))

#define ANGLE_MAX 0x2200
#define ANGLE_MIN 0
#define ANGLE_OFFSET 0x0680

static bool ShouldFilter(short angle, short& pressed, short& hold)
{
    if (!(hold & U_JPAD))
        return false;

    if (angle > 0x6000)
        return false;
    if (angle < -0x6000)
        return false;
    
    pressed &= ~(U_JPAD);
    hold &= ~(U_JPAD);

    if (0x1010 < angle || angle > -0x1010)
        return false;

    return true;
}

void TwoD::Init()
{
    CONFIG->Angle = 0x0900;
    CONFIG->Zooming = 0x441B;
}

extern s16 s8DirModeYawOffset;

#define oBparam12 (oBehParams & 0xffff0000)
#define oBparam34 (oBehParams & 0x0000ffff)

#define oBparam1 (oBehParams & 0xff000000)
#define oBparam2 (oBehParams & 0x00ff0000)
#define oBparam3 (oBehParams & 0x0000ff00)
#define oBparam4 (oBehParams & 0x000000ff)

void TwoD::Step()
{
    s8DirModeYawOffset -= oBparam12;
    if (oBparam3)
        gMarioStates->pos[2] = oPosZ;
    else
        gMarioStates->pos[0] = oPosX;
    
    short hold = gControllers[0].buttonDown;
    short pressed = gControllers[0].buttonPressed;

    if ((pressed & U_CBUTTONS) && CONFIG->Angle + ANGLE_OFFSET <= ANGLE_MAX)
    {
        CONFIG->Angle += ANGLE_OFFSET;
        CONFIG->Zooming += 0x15;
    }

    if ((pressed & D_CBUTTONS) && CONFIG->Zooming - ANGLE_OFFSET >= ANGLE_MIN)
    {
        CONFIG->Angle -= ANGLE_OFFSET;
        CONFIG->Zooming -= 0x15;
    };
    
    hold &= ~(U_CBUTTONS | D_CBUTTONS);
    pressed &= ~(U_CBUTTONS | D_CBUTTONS);

    short angle = gPlayerCameraState[0].faceAngle[1] - oBparam12;
    if (ShouldFilter(angle, pressed, hold))
    {
        if (angle > 0)
        {
            s8DirModeYawOffset = 0x2000;
            hold &= ~(R_JPAD | R_CBUTTONS);
            pressed &= ~(R_JPAD | R_CBUTTONS);
        }
        else
        {
            s8DirModeYawOffset = -0x2000;
            hold &= ~(L_JPAD | L_CBUTTONS);
            pressed &= ~(L_JPAD | L_CBUTTONS);
        }
    }
    else
    {
        if (s8DirModeYawOffset >= 0x2000)
        {
            s8DirModeYawOffset = 0x2000;
            hold &= ~(R_JPAD | R_CBUTTONS);
            pressed &= ~(R_JPAD | R_CBUTTONS);
        }
        if (s8DirModeYawOffset <= -0x2000)
        {
            s8DirModeYawOffset = -0x2000;
            hold &= ~(L_JPAD | L_CBUTTONS);
            pressed &= ~(L_JPAD | L_CBUTTONS);
        }
    }
    
    gControllers[0].buttonDown = hold;
    gControllers[0].buttonPressed = pressed;

    sSelectionFlags = 4;
    gCameraMovementFlags = 10;
    s8DirModeYawOffset += oBparam12;
}

int TwoD::Behavior[] = {
    0x0c000000, (int) sInit,
    0x08000000,
    0x0c000000, (int) sStep,
    0x09000000,
};