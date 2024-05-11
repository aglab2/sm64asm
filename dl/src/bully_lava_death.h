#pragma once

#include <sm64.h>
extern "C"
{
    #include <game/object_list_processor.h>
}

s8 objLavaDeathBullyThreeBullies(void);
s8 objLavaDeathBullySingleBully(void);

class ResetDeathFlags : Object
{
private:
    void Init();
    void Step();
    static void sInit() { reinterpret_cast<ResetDeathFlags*>(gCurrentObject)->Init(); }
    static void sStep() { reinterpret_cast<ResetDeathFlags*>(gCurrentObject)->Step(); }

public:
    static int Behavior[];
};

bool preStarSpawnInit(void);
void redCoinStarSpawnInit(void);
