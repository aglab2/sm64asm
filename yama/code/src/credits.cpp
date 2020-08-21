#include "credits.h"
extern "C"
{
    #include "game/camera.h"
    #include "game/game.h"
    #include "game/level_update.h"
    #include "game/memory.h"
    #include "game/object_helpers.h"
    #include "game/print.h"
    extern "C" void dma_copy(void* ramStart, void* romStart, void* romEnd);
}

constexpr int sCreditPartCount = 31;
constexpr int sCreditPartLength = 7670 / sCreditPartCount;

constexpr int sCreditPartSize = 0x21000;

#define oPart OBJECT_FIELD_S32(0x1b)
#define oMashedCount OBJECT_FIELD_S32(0x1c)
#define oLastPressed OBJECT_FIELD_S32(0x1d)

void Credits::Init()
{
    auto hud = (char*) segmented_to_virtual((void*) 0x02000000);
    for (int i = 0; i < 0x1400; i++)
        hud[i] = 0;

    for (int i = 0; i < 0x200; i++)
        (hud + 0x4800)[i] = 0;

    for (int i = 0; i < 0x200; i++)
        (hud + 0x4200)[i] = 0;

    oPart = 0;
}

void Credits::FunnyText()
{
    int mashedCount = oMashedCount;
    if (mashedCount < 100)
    {
        return;
    }
    else if (mashedCount < 200)
    {
        print_text_centered(160, 20, "STOP IT");
    }
    else if (mashedCount < 300)
    {
        print_text_centered(160, 20, "YOU CANT ESCAPE");
    }
    else if (mashedCount < 400)
    {
        print_text_centered(160, 20, "REALLY");
    }
    else if (mashedCount < 500)
    {
        print_text_centered(160, 20, "YOU ARE PERSISTENT");
    }
    else if (mashedCount < 600)
    {
        print_text_centered(160, 20, "DO IT ONE MORE TIME");
    }
    else if (mashedCount < 700)
    {
        print_text_centered(160, 20, "STILL GOING I SEE");
    }
    else if (mashedCount < 800)
    {
        print_text_centered(160, 20, "NOT TIRED YET");
    }
    else if (mashedCount < 900)
    {
        print_text_centered(160, 20, "EEEEEEEEEEEEEEEEEEEEEEEEEE");
    }
    else if (mashedCount < 1000)
    {
        print_text_centered(160, 20, "THOUSAND TIMES");
    }
    else if (mashedCount < 1100)
    {
        print_text_centered(160, 20, "BUY ME A CAR");
    }
    else if (mashedCount < 1300)
    {

    }
    else if (mashedCount < 1400)
    {
        print_text_centered(160, 20, "FINE YOU WONT STOP");
    }
    else if (mashedCount < 1500)
    {
        print_text_centered(160, 20, "FLIP A COIN NOW");
    }
    else if (mashedCount < 1600)
    {
        print_text_centered(160, 20, "DORRIE");
    }
    else
    {   
        oMashedCount = 0;
        spawn_object(this, 104, (BehaviorScript*) 0x13004F90);
    }
}

void Credits::Step()
{
    FunnyText();
    if (oLastPressed != gControllers->buttonPressed)
    {
        oMashedCount++;
    }
    oLastPressed = gControllers->buttonPressed;
    gControllers->buttonDown = 0;
    gControllers->buttonPressed = 0;
    gMarioStates->input = 0;

    gCameraMovementFlags = 10;

    if (oPart != sCreditPartCount && oTimer && 0 == oTimer % sCreditPartLength)
    {
        auto romStart = 0x03b80000 + sCreditPartSize * oPart;
        auto romEnd = romStart + sCreditPartSize;
        auto textures = segmented_to_virtual((void*) 0x0E000840);
        dma_copy(textures, (void*) romStart, (void*) romEnd);
        oPart++;
    }
}

uintptr_t Credits::Behavior[] = 
{
    0x0c000000, (uintptr_t) sInit,
    0x08000000,
    0x0c000000, (uintptr_t) sStep,
    0x09000000,
};