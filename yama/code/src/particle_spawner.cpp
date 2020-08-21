#include "particle_spawner.h"
extern "C"
{
    #include "game/object_helpers.h"
}

void ParticleSpawner::Step()
{
    spawn_object(this, 0, (const BehaviorScript*) 0x13002af0);
}

uintptr_t ParticleSpawner::Behavior[] = {
    0x08000000,
    0x0c000000, (uintptr_t) sStep,
    0x09000000,
};