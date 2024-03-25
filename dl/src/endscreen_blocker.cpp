#include "endscreen_blocker.h"

extern "C"
{
    #include <game/camera.h>
    #include <game/game.h>
    #include <game/mario.h>
    #include <game/object_helpers.h>
    #include <game/level_update.h>
    
    void set_camera_mode_8_directions(struct Camera *c);
}

void EndscreenBlocker::Init()
{
    set_cam_angle(2); // lakitu cam
    gHudDisplay.flags = HUD_DISPLAY_NONE;
}

void EndscreenBlocker::Step()
{
    set_mario_action(gMarioStates, 0, 0);
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