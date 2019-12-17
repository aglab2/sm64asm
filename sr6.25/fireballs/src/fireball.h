#pragma once

#include <sm64.h>

#define oAxis damage_to_mario
#define oKillBowser health

class FireBall : MObject
{
public:
    enum Actions
    {
        GROWING,
        WAITING,
        ACCELERATING,
        FLYING,
        EXPLODE,
        GO_BACK,
    };

private:
    void Init();
    void Step();

    void Growing();
    void Waiting();
    void Accelerating();
    void Flying();
    void Explode();
    void GoBack();
    
    static void sInit() { reinterpret_cast<FireBall*>(M64_CURR_OBJ_PTR)->Init(); }
    static void sStep() { reinterpret_cast<FireBall*>(M64_CURR_OBJ_PTR)->Step(); }

public:
    static int Behavior[];
};

class FireBallTail : MObject
{
    template<int Count>
    void ShakeVertices(int segFrom);

    void Init();
    void Step();
    static void sInit() { reinterpret_cast<FireBallTail*>(M64_CURR_OBJ_PTR)->Init(); }
    static void sStep() { reinterpret_cast<FireBallTail*>(M64_CURR_OBJ_PTR)->Step(); }

public:
    static int Behavior[];
};
