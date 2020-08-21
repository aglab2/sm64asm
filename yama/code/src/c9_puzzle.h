#pragma once

extern "C"
{
    #include "types.h"
    #include "game/object_list_processor.h"
}
#include "object_fields.h"

class C9Puzzle : public Object
{
    using Type = C9Puzzle;
    using IndexedFunc = void (*)(void* ctx, int i, int j);

    enum class Types
    {
        INVALID = 0b00,
        COINS   = 0b01,
        FIGHT   = 0b10,
        MUSIC   = 0b11,
    };

#define PROXIED_FUNCTION(x) void x(); static void s##x() { return reinterpret_cast<Type*>(gCurrentObject)->x(); }

    PROXIED_FUNCTION(Init)
    PROXIED_FUNCTION(Step)
    
#undef PROXIED_FUNCTION

    void getIndices(int* i, int* j);
    void checkOffsets(int i, int j);

    void spawnCoins(int i, int j);
    void spawnFight(int i, int j);

    void Coins();
    void Fight();
    void Music();

    void finishChallenge(bool success);
    
    void forAllValidIndicesAround(int i, int j, IndexedFunc fn);
    Types getType(int i, int j);
    void getPos(int i, int j, float* x, float* z);

public:
    static uintptr_t Behavior[];
};