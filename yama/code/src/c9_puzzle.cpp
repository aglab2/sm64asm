#include "c9_puzzle.h"
extern "C"
{
    #include "audio_defines.h"
    #include "audio/external.h"
    #include "game/game.h"
    #include "game/level_update.h"
    #include "game/memory.h"
    #include "game/object_helpers.h"
    #include "game/print.h"
    #include "game/spawn_sound.h"
    #include "engine/behavior_script.h"
    #include "engine/surface_load.h"
    
    extern "C" void play_sequence(u8 player, u8 seqId, u16 fadeTimer);
}
#include "f2_scroll.h"

constexpr auto sMapTopX1 = 20.f;
constexpr auto sMapTopZ1 = -10185.f;
constexpr auto sMapTopX2 = 20.f;
constexpr auto sMapTopZ2 = 7907.f;
constexpr auto sMapStep = 793.f;
constexpr auto sTime = 10;

constexpr auto sMusicBase = 0x07030000; // music id -> course id
constexpr auto sCourseNameBase = 0x07030100; // course id -> char[32]

constexpr auto sMusicIdMin = 0x23;
constexpr auto sMusicIdMid   = 0x3a;
constexpr auto sMusicIdMax = 0x53;
constexpr auto sCourseMax = 0x19;

#define oNextI OBJECT_FIELD_S32(0x1b)
#define oNextJ OBJECT_FIELD_S32(0x1c)

#define oPickedCombo OBJECT_FIELD_S32(0x1d)

#define oCorrectAnswer OBJECT_FIELD_S16(0x1d, 0)
#define oPickedAnswer OBJECT_FIELD_S16(0x1d, 1)
#define oAnswers ((short*) &OBJECT_FIELD_S16(0x1e, 0))

static int oObjToDespawn = 0;

enum class Actions
{
    INIT,
    COINS,
    FIGHT,
    MUSIC,
    TEXT,
};

struct Combo
{
    unsigned char model;
    uintptr_t behavior;
};

static Combo sCombos1[] = 
{
    { 105, 0x13005468 }, // skeeter
    { 192, 0x1300472C }, // goomba
};

static Combo sCombos2[] = 
{
    { 220, 0x130046DC }, // fly guy
    { 192, 0x1300472C }, // goomba 
};

static u8 sMap1[] = {
    0b00000110,
    0b00001011,
    0b11100101,
    0b10010110,
    0b01110001,
    0b10011011,
};

static u8 sMap2[] = {
    0b10110000,
    0b11010000,
    0b01101101,
    0b10110110,
    0b01001101,
    0b10011011,
};

static int sTriggeredPieces1 = 0;
static int sTriggeredPieces2 = 0;

static void markPiece(int buff, int i, int j)
{
    auto idx = i * 4 + j;
    if (buff)
    {
        sTriggeredPieces2 |= 1 << idx;
    }
    else
    {
        sTriggeredPieces1 |= 1 << idx;
    }
}

static bool pieceMarked(int buff, int i, int j)
{
    auto idx = i * 4 + j;
    if (buff)
    {
        return sTriggeredPieces2 & (1 << idx);
    }
    else
    {
        return sTriggeredPieces1 & (1 << idx);
    }
}

void C9Puzzle::getPos(int i, int j, float* x, float* z)
{
    auto x0 = oBehParams2ndByte ? sMapTopX2 : sMapTopX1;
    auto z0 = oBehParams2ndByte ? sMapTopZ2 : sMapTopZ1;

    *x = x0 + i * sMapStep;
    *z = z0 + j * sMapStep;
}

C9Puzzle::Types C9Puzzle::getType(int i, int j)
{
    if (i < 0 || i > 5)
        return Types::INVALID;
    if (j < 0 || j > 3)
        return Types::INVALID;

    u8* map = oBehParams2ndByte ? sMap2 : sMap1;
    auto value = map[i];
    return (Types) ((value >> (2 * j)) & 0b11);
}

void C9Puzzle::forAllValidIndicesAround(int i, int j, IndexedFunc fn)
{
    if (Types::INVALID != getType(i + 1, j))
        fn(this, i + 1, j);
    if (Types::INVALID != getType(i - 1, j))
        fn(this, i - 1, j);
    if (Types::INVALID != getType(i, j + 1))
        fn(this, i, j + 1);
    if (Types::INVALID != getType(i, j - 1))
        fn(this, i, j - 1);
}

void C9Puzzle::finishChallenge(bool success)
{
    if (!success)
    {
        auto damage = 0x400;
        if (gMarioStates->health < damage)
            gMarioStates->health = 0;
        else
            gMarioStates->health -= damage;
    }
    
    switch ((Types)((int) oAction - 1))
    {
        case Types::COINS:
            oObjToDespawn = 0x408114;
            break;
        case Types::FIGHT:
        {
            auto& config = oBehParams2ndByte ? sCombos2[oPickedCombo] : sCombos1[oPickedCombo];
            oObjToDespawn = config.behavior;
        }
            break;
        case Types::MUSIC:
        {
            if (oBehParams2ndByte)
            {
                play_sequence(0, 4, 0);
            }
            else
            {
                play_sequence(0, 3, 0);
            }
        }
            break;
        default:
            break;
    }

    oAction = (int) Actions::INIT;
    getPos(oNextI, oNextJ, &oPosX, &oPosZ);
    gMarioStates->pos[0] = oPosX;
    gMarioStates->pos[1] = oPosY;
    gMarioStates->pos[2] = oPosZ;
    gMarioStates->vel[0] = 0;
    gMarioStates->vel[1] = 0;
    gMarioStates->vel[2] = 0;
    gMarioStates->action = 0x386;
}

void C9Puzzle::Coins()
{
    print_text_centered(160, 210, "GET COINS");
    if (oTimer == 0)
    {
        int i, j;
        getIndices(&i, &j);
        forAllValidIndicesAround(i, j, [](void* ctx, int i, int j)
        {
            reinterpret_cast<C9Puzzle*>(ctx)->spawnCoins(i, j);
        });
    }
    else
    {
        f32 d;
        if (nullptr == obj_find_nearest_object_with_behavior((const BehaviorScript*) 0x408114, &d))
            finishChallenge(true);
    }
}

void C9Puzzle::Fight()
{
    print_text_centered(160, 210, "KILL ENEMIES");
    if (oTimer == 0)
    {
        oPickedCombo = RandomU16() % 2;
        int i, j;
        getIndices(&i, &j);
        forAllValidIndicesAround(i, j, [](void* ctx, int i, int j)
        {
            reinterpret_cast<C9Puzzle*>(ctx)->spawnFight(i, j);
        });
    }
    else
    {
        auto& config = oBehParams2ndByte ? sCombos2[oPickedCombo] : sCombos1[oPickedCombo];
        f32 d;
        if (nullptr == obj_find_nearest_object_with_behavior((const BehaviorScript*) config.behavior, &d))
            finishChallenge(true);
    }
}

static int randomCourse(char* present, int& count)
{
    int coursenum = RandomFloat() * count;
    
    int idx = 0;
    int i = 0;

    while (present[idx]) idx++;
    for (; i < coursenum; i++)
    {
        idx++;
        while (present[idx]) idx++;
    }

    present[idx] = true;
    count--;
    return idx;
}

extern "C" u16 gRandomSeed16;
void C9Puzzle::Music()
{
    print_text_centered(140, 210, "PICK SONG WITH L");
    print_text_centered(140, 190, "USE DPAD UP DOWN");

    if (oTimer == 0)
    {
        oPickedAnswer = 0;
        char pickedCourses[sCourseMax] = {};
        auto pickedCoursesCount = sCourseMax;

        auto musicStart = oBehParams2ndByte ? sMusicIdMid : sMusicIdMin;
        auto musicLen   = oBehParams2ndByte ? (sMusicIdMax - sMusicIdMid) : (sMusicIdMid - sMusicIdMin);

        int song = musicStart + RandomFloat() * musicLen;
        play_sequence(0, song, 0);
        
        oCorrectAnswer = RandomU16() % 4;
        auto song2course = reinterpret_cast<char*>(segmented_to_virtual((void*) sMusicBase));
        auto correctCourse = song2course[song] - 1;
        oAnswers[oCorrectAnswer] = correctCourse;
        pickedCourses[correctCourse] = true;
        pickedCoursesCount--;
        for (int i = 0; i < 4; i++)
        {
            if (i != oCorrectAnswer)
            {
                oAnswers[i] = randomCourse(pickedCourses, pickedCoursesCount);
            }
        }
    }
    else
    {
        auto courseNames = reinterpret_cast<char*>(segmented_to_virtual((void*) sCourseNameBase));
        auto buttonsPressed = gControllers->buttonPressed;
        /*
        if (!oPickedAnswer)
            oPickedAnswer = sMusicIdMin;
        if (buttonsPressed & D_JPAD)
            oPickedAnswer++;
        if (buttonsPressed & U_JPAD)
            oPickedAnswer--;
            
        if (oPrevPickedAnswer != oPickedAnswer)
        {
            oPrevPickedAnswer = oPickedAnswer;
            play_sequence(0, oPickedAnswer, 0);
        }

        auto song2course = reinterpret_cast<char*>(segmented_to_virtual((void*) sMusicBase));
        auto course = song2course[oPickedAnswer] - 1;
        print_text(40, 150, courseNames + 32 * course + 29);
        print_text(80, 150, courseNames + 32 * course);
        */
        for (int i = 0; i < 4; i++)
        {
            auto course = oAnswers[i];
            print_text(40, 150 - 30 * i, courseNames + 32 * course + 29);
            print_text(80, 150 - 30 * i, courseNames + 32 * course);
        }
        print_text(20, 150 - 30 * oPickedAnswer, "*");
        if (oPickedAnswer != 3 && buttonsPressed & D_JPAD)
            oPickedAnswer++;
        if (oPickedAnswer != 0 && buttonsPressed & U_JPAD)
            oPickedAnswer--;

        if (buttonsPressed & L_TRIG)
            finishChallenge(oPickedAnswer == oCorrectAnswer);
    }
}

void C9Puzzle::spawnCoins(int i, int j)
{
    if (i == oNextI && j == oNextJ)
        return;

    auto obj = spawn_object(this, 118, (BehaviorScript*) 0x408114);
    auto extraY = 50.f + 500.f * RandomFloat();
    if (oBehParams2ndByte)
        extraY *= 1.5f;
    
    obj->oPosY += extraY;
    getPos(i, j, &obj->oPosX, &obj->oPosZ);
}

void C9Puzzle::spawnFight(int i, int j)
{
    if (i == oNextI && j == oNextJ)
        return;

    auto& config = oBehParams2ndByte ? sCombos2[oPickedCombo] : sCombos1[oPickedCombo];
    auto obj = spawn_object(this, config.model, (BehaviorScript*) config.behavior);
    obj->oBehParams2ndByte = oBehParams2ndByte;
    obj->oBehParams = oBehParams;
    getPos(i, j, &obj->oPosX, &obj->oPosZ);
}

static float distance(float x1, float y1, float z1, float x2, float y2, float z2)
{
    return (x1-x2) * (x1-x2) + (y2 - y1) * (y2 - y1) + (z1-z2) * (z1-z2);
}

void C9Puzzle::getIndices(int* i, int* j)
{
    auto x0 = oBehParams2ndByte ? sMapTopX2 : sMapTopX1;
    auto z0 = oBehParams2ndByte ? sMapTopZ2 : sMapTopZ1;
    *i = (oPosX - x0) / sMapStep;
    *j = (oPosZ - z0) / sMapStep;
}

void C9Puzzle::checkOffsets(int i, int j)
{
    float x, z;
    getPos(i, j, &x, &z);
    float y = 660.f;

    auto particle = spawn_object(this, 0, (const BehaviorScript*) 0x13002af0);
    particle->oPosX = x;
    particle->oPosY = y;
    particle->oPosZ = z;

    float dist = distance(x, y, z, gMarioObject->oPosX, gMarioObject->oPosY, gMarioObject->oPosZ);
    if (dist < 30000.f)
    {
        auto marked = pieceMarked(oBehParams2ndByte, i, j);
        markPiece(oBehParams2ndByte, i, j);

        if (!marked)
        {
            oNextI = i;
            oNextJ = j;
            auto type = getType(i, j);
            oAction = (int) type + 1;
        }
        else
        {
            getPos(i, j, &oPosX, &oPosZ);
        }
    }
}

void C9Puzzle::Init()
{
    auto x0 = oBehParams2ndByte ? sMapTopX2 : sMapTopX1;
    auto z0 = oBehParams2ndByte ? sMapTopZ2 : sMapTopZ1;
    oCollisionDistance = 2000.f;
    if (!oBehParams2ndByte)
    {
        sTriggeredPieces1 = 0;
        oPosX = x0 + 5.f * sMapStep;
        oPosZ = z0 + 3.f * sMapStep;
    }
    else
    {
        sTriggeredPieces2 = 0;
        oPosX = x0 + 0.f * sMapStep;
        oPosZ = z0 + 1.f * sMapStep;
    }
}

void C9Puzzle::Step()
{
    {
        f32 d;
        auto obj = obj_find_nearest_object_with_behavior((const BehaviorScript*) oObjToDespawn, &d);
        if (nullptr != obj)
            obj->activeFlags = 0;
        else
            oObjToDespawn = 0;
    }
    Scroll(0, -2, 0x07020BE0);
    load_object_collision_model();

    if (oAction == (int) Actions::INIT)
    {
        int curI, curJ;
        getIndices(&curI, &curJ);

        /*
        print_text_fmt_int(20, 80, "%d", curI);
        print_text_fmt_int(40, 80, "%d", curJ);

        print_text_fmt_int(20, 40, "%d", (int) getType(curI + 1, curJ));
        print_text_fmt_int(60, 40, "%d", (int) getType(curI - 1, curJ));
        print_text_fmt_int(40, 20, "%d", (int) getType(curI, curJ - 1));
        print_text_fmt_int(40, 60, "%d", (int) getType(curI, curJ + 1));
        */

        forAllValidIndicesAround(curI, curJ, [](void* ctx, int i, int j)
        {
            reinterpret_cast<C9Puzzle*>(ctx)->checkOffsets(i, j);
        });
    }
    else
    {
        switch ((Types)((int) oAction - 1))
        {
            case Types::INVALID:
                break;
            case Types::COINS:
                Coins();
                break;
            case Types::FIGHT:
                Fight();
                break;
            case Types::MUSIC:
                Music();
                break;
        }

        if (oTimer > sTime * 30)
            finishChallenge(false);

        print_text_fmt_int(20, 210, "%d", sTime - oTimer / 30);
    }
}

uintptr_t C9Puzzle::Behavior[] = {
    0x11010001,
    0x0c000000, (uintptr_t) sInit,
    0x2a000000, 0x07020D50,
    0x08000000,
    0x0c000000, (uintptr_t) sStep,
    0x09000000,
};