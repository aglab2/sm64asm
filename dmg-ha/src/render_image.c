
#include "render_image.h"

#include "game/game.h"
#include "game/print.h"

static inline s32 roundf(f32 in)
{
    f32 tmp;
    s32 out;
    __asm__("round.w.s %0,%1" : "=f" (tmp) : "f" (in ));
    __asm__("mfc1      %0,%1" : "=r" (out) : "f" (tmp));
    return out;
}

void draw_sprite(Gfx **dl, const void *texture, s32 dlImgFormat, s32 dlImgSize, s32 bilerp,
u32 textureWidth, u32 textureHeight, f32 x, f32 y, f32 displayWidth, f32 displayHeight, u8 alpha) {
    Gfx* gRenderImageGfxPool = (Gfx*) (0x80026000 + 0x30000);

    Gfx *dlHead = gRenderImageGfxPool;
    s32 sizeLoad = dlImgSize;
    s32 sizeLine = dlImgSize;
    s32 shift = 0;
    
    gDPPipeSync        (dlHead++);
    gDPSetTexturePersp (dlHead++, G_TP_NONE);
    gDPSetCombineMode  (dlHead++, G_CC_FADEA, G_CC_FADEA);
    gDPSetTextureFilter(dlHead++, G_TF_POINT);
    gDPSetCycleType    (dlHead++, G_CYC_1CYCLE);
    gDPSetRenderMode   (dlHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetEnvColor     (dlHead++, 255, 255, 255, alpha);

    if (displayWidth <= 0.0f || displayHeight <= 0.0f) {
        // Cannot display negative width/height
        return;
    }

    u32 shiftedDisplayWidth = (u32) roundf(displayWidth * 4.0f);
    u32 shiftedDisplayHeight = (u32) roundf(displayHeight * 4.0f);
    s32 shiftedX = roundf(x * 4.0f);
    s32 shiftedY = roundf(y * 4.0f);

    if (shiftedDisplayWidth == 0 || shiftedDisplayHeight == 0 || textureWidth == 0 || textureHeight == 0) {
        // Div by 0
        return;
    }

    u32 cw = 16 * (0x2448 >> (4 * dlImgSize) & 0xF);
    u32 ch = 16 * (0x2244 >> (4 * dlImgSize) & 0xF);
    u32 dsdx = ((0x400 * 4 * textureWidth ) + (shiftedDisplayWidth  / 2)) / shiftedDisplayWidth;
    u32 dtdy = ((0x400 * 4 * textureHeight) + (shiftedDisplayHeight / 2)) / shiftedDisplayHeight;

    if (dlImgSize == G_IM_SIZ_4b) {
        sizeLoad = G_IM_SIZ_8b;
        shift = 1;
    }
    if (dlImgSize == G_IM_SIZ_32b) {
        sizeLine = G_IM_SIZ_16b;
    }
    if (bilerp) {
        cw -= 2 << shift;
        ch -= 2 << shift;
    }

    gDPSetTextureImage(dlHead++, dlImgFormat, sizeLoad, textureWidth >> shift, texture);

    for (u32 ty = 0; ty < textureHeight; ty += ch) {
        u32 ult = ty;
        u32 lrt = ty + ch;
        if (lrt > textureHeight) {
            lrt = textureHeight;
        }

        s32 yl = shiftedY + ult * shiftedDisplayHeight / textureHeight;
        s32 yh = shiftedY + lrt * shiftedDisplayHeight / textureHeight;
        if (yh < 0 || yl > 4096) {
            continue;
        }

        s32 t = ult << 5;
        if (yl < 0) {
            t -= (yl * dtdy) >> 7;
            yl = 0;
        }

        if (bilerp) {
            if (ult > 0) {
                ult -= (1 << shift);
            }
            if (lrt < textureHeight) {
                lrt += (1 << shift);
            }
            t -= 16;
        }

        for (u32 tx = 0; tx < textureWidth; tx += cw) {
            u32 uls = tx;
            u32 lrs = tx + cw;
            if (lrs > textureWidth) {
                lrs = textureWidth;
            }

            s32 xl = shiftedX + uls * shiftedDisplayWidth / textureWidth;
            s32 xh = shiftedX + lrs * shiftedDisplayWidth / textureWidth;
            if (xh < 0 || xl > 4096) {
                continue;
            }

            s32 s = uls << 5;
            if (xl < 0) {
                s -= (xl * dsdx) >> 7;
                xl = 0;
            }

            if (bilerp) {
                if (uls > 0) {
                    uls -= (1 << shift);
                }
                if (lrs < textureWidth) {
                    lrs += (1 << shift);
                }
                s -= 16;
            }

            u32 line = (((lrs - uls) << sizeLine) + 14) >> 4;

            gDPPipeSync(dlHead++);
            gDPSetTile(dlHead++, dlImgFormat, sizeLoad, line, 0, 0, 0, 0, 0, 0, 0, 0, 0);
            gDPLoadSync(dlHead++);
            gDPLoadTile(
                dlHead++, 0,
                (uls    ) << G_TEXTURE_IMAGE_FRAC >> shift,
                (ult    ) << G_TEXTURE_IMAGE_FRAC,
                (lrs - 1) << G_TEXTURE_IMAGE_FRAC >> shift,
                (lrt - 1) << G_TEXTURE_IMAGE_FRAC);
            gDPSetTile(
                dlHead++, dlImgFormat, dlImgSize, line, 0, 0, 0,
                G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
            gDPSetTileSize(
                dlHead++, 0,
                (uls    ) << G_TEXTURE_IMAGE_FRAC,
                (ult    ) << G_TEXTURE_IMAGE_FRAC,
                (lrs - 1) << G_TEXTURE_IMAGE_FRAC,
                (lrt - 1) << G_TEXTURE_IMAGE_FRAC);
            gSPTextureRectangle(dlHead++, xl, yl, xh, yh, 0, s, t, dsdx, dtdy);
        }
    }

    gDPPipeSync(dlHead++);
    gDPSetTexturePersp(dlHead++ , G_TP_PERSP);
    gDPSetCombineMode(dlHead++  , G_CC_SHADE, G_CC_SHADE);
    gDPSetTextureFilter(dlHead++, G_TF_BILERP);
    gSPEndDisplayList(dlHead++);

    gSPDisplayList((*dl)++, 0x26000 + 0x30000);
}
