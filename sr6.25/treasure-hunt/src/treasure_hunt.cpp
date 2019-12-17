#include "treasure_hunt.h"

#include <graphics.h>
#include <ultra/gu.h>

static int sGFXTexture = 0;

void TreasureHunt::Step()
{
    // Check if YS is on
    auto flags = SaveFile_GetFlags();
    if (!(flags & 0x000200))
        return;

    auto count = SaveFile_GetStarFlags(gCurrSaveFileNum - 1, gCurrCourseNum - 1);
    if (gCurrCourseNum == 24) // if it is YS palace course
    {
        if (count & 0b01000000)
            return;
    }
    else
    {
        if (count != 0b10111111)
            return;
    }

    float dist = DistanceFromObject(M64_MARIO_OBJ_PTR, rootObj);
    if (dist > 20000.0f)
        return;

    int textureBase = 0x04048000;
    if (dist < 750.0f) // orig 500
    {
        // this is yellow box
        textureBase = 0x0404C000;
    }
    else if (dist < 2000.0f) // orig 1500
    {
        // this is red
        textureBase = 0x0404B000;
    }
    else if (dist < 5000.0f)
    {
        textureBase = 0x0404A000;
    }
    else if (dist < 10000.0f)
    {
        textureBase = 0x04049000;
    }

    int flashTime = 1 + dist / 500.0f;
    if (timer > flashTime)
    {
        action++;
        action = action % 3;
    }

    sGFXTexture = textureBase + 0x200 * action;

    //PrintInt(40, 170, "%d", (int) dist);
}

static void AddTexture(int texture)
{
    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture);
    gSPDisplayList(gDisplayListHead++, 0x02011af8);
}

void TreasureHunt::Draw()
{
    if (!sGFXTexture)
        return;

    AddTexture(sGFXTexture);
    RenderTexRect(22, 170, 0);
    sGFXTexture = 0;
}

int TreasureHunt::Behavior[] = {
    0x08000000,
    0x0C000000, (int) sStep,
    0x09000000,
};