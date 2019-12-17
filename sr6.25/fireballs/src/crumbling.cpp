#include "crumbling.h"

enum Actions
{
    INIT,
    FALLING_DOWN,
    DYING,
};

#define FALLING_ACCELERATION 0.1f
#define FALLING_DOWN 100
#define DEATH_TIME 150

void Crumbling::Init()
{
    if (IsMarioStepping())
    {
        PlaySoundProperly(0x302d8081);
        ShakeScreen(1);
        action = FALLING_DOWN;
        model = 1;
    }

    ProcessCollision();
}

void Crumbling::FallingDown()
{
    if (timer > FALLING_DOWN)
        action = DYING;

    speed.y -= FALLING_ACCELERATION;
    pos.y += speed.y;
    
    ProcessCollision();
}

void Crumbling::Dying()
{
    if (timer == 0)
    {
        for (int i = 0; i < 8; i++)
        {
            auto piece = SpawnObj(this, 0xF6, 0x40930c);
            piece->model = i;
            piece->speed = speed;
            piece->speedRotationPitch = GetRNG() / 100;
            piece->absspeed = 3.0f;
        }
        HideObject();
        PlaySoundProperly(0x302e2081);
    }

    if (timer > DEATH_TIME)
    {
        pos = posInit;
        speed.y = 0;
        UnHideObject();
        model = 0;
        action = INIT;
    }
}

void Crumbling::Step()
{
    switch (action)
    {
        case INIT: return Init();
        case FALLING_DOWN: return FallingDown();
        case DYING: return Dying();
    }
}

int Crumbling::Behavior[] = 
{
    0x2a000000, 0x0404DAE0,
    0x11010001,
    0x2d000000,
    0x0E430800,
    0x08000000,
    0x0c000000, (int) sStep,
    0x09000000,
};
