#pragma once

#include "types.h"

u32 setMarioActionOnStarGrab(struct MarioState *m, u32 action, u32 actionArg);
s16 setDoorStarCount(struct MarioState *m, UNUSED u32 interactType, struct Object *o);
s16 setDoorStarCurrent(struct Object *o, int from, int to);
u32 getTextBoxForStarCount(s16 requiredNumStars, struct Object *o);
void afterStarInit();
s32 renderCourseCompleteBlueStar();
s32 starNoExitSelect(struct MarioState *m, u32 interactType, struct Object *o);
void starAfterStarDanceNonStop(struct MarioState *m, s32 isInWater);
void spawnDialogBoxForNonStopStar(u8 lastCompletedStarNum);
