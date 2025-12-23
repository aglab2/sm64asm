#pragma once

#include "types.h"

void draw_sprite(Gfx **dl, const void *texture, s32 dlImgFormat, s32 dlImgSize, s32 bilerp, u32 textureWidth, u32 textureHeight, f32 x, f32 y, f32 displayWidth, f32 displayHeight, u8 alpha);
