#include "endscreen_blocker.h"

extern "C"
{
    #include <game/camera.h>
    #include <game/display.h>
    #include <game/game.h>
    #include <game/mario.h>
    #include <game/object_helpers.h>
    #include <game/level_update.h>
    #include <game/print.h>
    #include <engine/math_util.h>
    #include <level_table.h>
    
    void set_camera_mode_8_directions(struct Camera *c);
}

#define SHOW_TEXT_TIME 135
#define FRAMES_PER_LETTER 2

void EndscreenBlocker::Init()
{
    auto o = gCurrentObject;
    set_cam_angle(2); // lakitu cam
    gHudDisplay.flags = HUD_DISPLAY_NONE;
    o->oHealth = 0;
}

static void printFancy(int yoff, const char* str, int renderLimit)
{
    int len = 0;
    while (str[len] != '\0')
    {
        len++;
    }

    int symbolLen = 11;
    int halfLen = len / 2;
    int x = 160 - halfLen * symbolLen;
    for (int i = 0; i < len; i++)
    {
        if ((renderLimit -= FRAMES_PER_LETTER) < 0)
            break;

        int yoff2 = sins(gGlobalTimer * 0x400 + i * 0x700) * 5;

        if (' ' == str[i])
        {
            continue;
        }

        char strProcessed[2] = { str[i], '\0' };
        print_text_centered(x + i * symbolLen, 30 - 20 * yoff + yoff2, strProcessed);
    }
}

void EndscreenBlocker::Step()
{
    auto m = gMarioStates;
    auto o = gCurrentObject;
    o->oHealth++;

    if (1 == o->oAction && o->oTimer > 15)
    {
        set_mario_action(m, ACT_IDLE, 0);
        o->activeFlags = 0;
        return;
    }
    if (0 == o->oAction && o->oTimer > SHOW_TEXT_TIME)
    {
        if (gMarioStates->numStars == 333)
        {
            printFancy(0, "THANK YOU SO MUCH", o->oHealth - SHOW_TEXT_TIME);
            printFancy(1, "FOR PLAYING THE HACK", o->oHealth - SHOW_TEXT_TIME - FRAMES_PER_LETTER * sizeof("THANK YOU SO MUCH"));
        }
        else if (gMarioStates->numStars >= 150)
        {
            printFancy(0, "THANK YOU FOR PLAYING", o->oHealth - SHOW_TEXT_TIME);
            printFancy(1, "TRY TO GET ALL 333 STARS", o->oHealth - SHOW_TEXT_TIME - FRAMES_PER_LETTER * sizeof("THANK YOU FOR PLAYING"));
        }
        else
        {
            printFancy(0, "THANK YOU FOR PLAYING", o->oHealth - SHOW_TEXT_TIME);
            printFancy(1, "TRY TO GET ALL 150 STARS", o->oHealth - SHOW_TEXT_TIME - FRAMES_PER_LETTER * sizeof("THANK YOU FOR PLAYING"));
        }
        if (gPlayer1Controller->buttonPressed & L_TRIG)
        {
            m->usedObj = o;
            o->oBehParams = 0xa << 16;
            o->oBehParams2ndByte = 0xa;
            level_trigger_warp(m, WARP_OP_WARP_OBJECT);
            o->oAction = 1;
        }
    }

    set_mario_action(m, 0, 0);
    gMarioObject->header.gfx.sharedChild = gLoadedGraphNodes[0];
    gPlayer1Controller->buttonDown = 0;
    gPlayer1Controller->buttonPressed = 0;
    gPlayer1Controller->stickX = 0;
    gPlayer1Controller->stickY = 0;
    gPlayer1Controller->rawStickX = 0;
    gPlayer1Controller->rawStickY = 0;
    auto camera = gCurrentArea->camera;
    set_camera_mode_8_directions(camera);
    reset_camera(camera);
}

int EndscreenBlocker::Behavior[] =
{
    0x0c000000, (int) sInit,
    0x08000000,
    0x0c000000, (int) sStep,
    0x09000000,
};