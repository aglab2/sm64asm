#include "empty.h"

void EmptyObject::Init()
{
    // fill me
}

void EmptyObject::Step()
{
    // fill me
}

int EmptyObject::Behavior[] =
{
    0x0C000000, (int) sInit,
    0x08000000,
    0x0C000000, (int) sStep,
    0x09000000,    
};