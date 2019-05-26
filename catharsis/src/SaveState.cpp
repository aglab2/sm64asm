#include "SaveState.h"
#include <inputs.h>

static int StateSize    = 0x26B28;
static void* DataStart  = (void*) 0x8033B170;
static void* StateStart = (void*) 0x80780000;

void SaveState::Save()
{
    memcpy(StateStart, DataStart, StateSize);
}

void SaveState::Load()
{
    memcpy(DataStart, StateStart, StateSize);
}

void SaveState::Step()
{
    // Mask button
    M64_CONTROLLER1_BUTTONS_HOLD  &= ~(BUTTON_START);
    M64_CONTROLLER1_BUTTONS_PRESS &= ~(BUTTON_START);
    
    Mario* mario = M64_MARIO_STRUCT;
    CollisionTriangle* tri = mario->curr_collision_triangle;

    if (M64_CONTROLLER1_BUTTONS_PRESS & BUTTON_L)
        return Load();

    if ((M64_MARIO_STRUCT->action & 0xFFFFF000) == 0x00021000)
        return Load();

    if ((SM64Health & 0xFF00) == 0)
        return Load();

    if (prevCollision != 0x30 && tri->collision_type == 0x30)
        return Save();
        
    prevCollision = tri->collision_type; 
}

int SaveState::Behavior[] =
{
    0x08000000,
    0x0C000000, (int) sStep,
    0x09000000,    
};