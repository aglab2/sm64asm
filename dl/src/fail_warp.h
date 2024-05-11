#pragma once

#include "types.h"

void setSafePos(struct MarioState *m);
struct ObjectWarpNode* areaGetWarpNode(u8 id);
void preLevelTriggerWarp(struct MarioState *m, s32* warpOp);
void initMarioAfterQuickWarp(struct MarioState *m);
void initMarioAfterQuickWarpResetCamera(struct ObjectWarpNode *spawnNode);
void marioSetSafePos(struct MarioState *m, struct Surface *floor);

void triggerFailWarp(struct MarioState* m);
