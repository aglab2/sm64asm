#include "rooms_coll.h"
extern "C"
{
    #include "game/level_update.h"
    #include "game/memory.h"
    
    extern void play_sequence(u8 player, u8 seqId, u16 fadeTimer);
}

static int sCollisions[] = { 0x37, 0x15, 0x1b, 0x1a };
static int sSongs[] = { 59, 60, 61, 62 };

constexpr int sTransWallsCollision = 0x1c;
constexpr int sTransWallsPtr = 0x0E046E40;

#define oPrevCollision OBJECT_FIELD_S32(0x1b)
#define oLastSong OBJECT_FIELD_S32(0x1c)

void RoomsColl::PlaySequence(int seq)
{
    if (seq != oLastSong)
    {
        play_sequence(0, seq, 0);
        oLastSong = seq;
    }
}

void RoomsColl::Init()
{
}

void RoomsColl::Step()
{
    auto floor = gMarioStates->floor;
    if (!floor)
        return;

    auto coll = floor->type;

    if (oPrevCollision != coll)
    {
        for (int i = 0; i < 4; i++)
            if (coll == sCollisions[i])
                PlaySequence(sSongs[i]);
        
        auto ptr = (char*) segmented_to_virtual((void*) sTransWallsPtr);
        if (coll == sTransWallsCollision)
        {
            PlaySequence(sSongs[1]);
            ptr[7] = 0x10;
        }
        else
        {
            ptr[7] = 0xff;
        }
    }

    oPrevCollision = coll;
}

int RoomsColl::Behavior[] = {
    // 0x0c000000, (int) sInit,
    0x08000000,
    0x0c000000, (int) sStep,
    0x09000000,
};