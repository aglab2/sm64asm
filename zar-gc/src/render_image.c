
#include "render_image.h"

#include "game/game.h"
#include "game/print.h"

static inline void* alloc(char** pool, size_t size)
{
    *pool -= size;
    return *pool;
}

static const int xuv = 8098;
static const int yuv = 974;

static void render_piece(char** pool, int x, int y, int posW, int posH, int imW, int imH)
{
    const int xoff = -15;
    const int yoff = 352;

    int x0 = xoff + (x + posW);
    int y0 = yoff - (y + posH);
    
    int x1 = xoff + (x + posW) + imW;
    int y1 = yoff - (y + posH) + imH;

    x0 /= 1.5f;
    x1 /= 1.5f;
    y0 /= 1.5f;
    y1 /= 1.5f;

    Vtx* vbuf = (Vtx*) alloc(pool, 4 * 16);
    vbuf[0].v.ob[0] = x0;
    vbuf[0].v.ob[1] = y0;
    vbuf[0].v.ob[2] = 0;
    vbuf[0].v.flag = 0;
    vbuf[0].v.tc[0] = 0;
    vbuf[0].v.tc[1] = yuv;
    vbuf[0].v.cn[0] = 0xff;
    vbuf[0].v.cn[1] = 0xff;
    vbuf[0].v.cn[2] = 0xff;
    vbuf[0].v.cn[3] = 0xff;
    
    vbuf[1].v.ob[0] = x1;
    vbuf[1].v.ob[1] = y0;
    vbuf[1].v.ob[2] = 0;
    vbuf[1].v.flag = 0;
    vbuf[1].v.tc[0] = xuv;
    vbuf[1].v.tc[1] = yuv;
    vbuf[1].v.cn[0] = 0xff;
    vbuf[1].v.cn[1] = 0xff;
    vbuf[1].v.cn[2] = 0xff;
    vbuf[1].v.cn[3] = 0xff;

    vbuf[2].v.ob[0] = x1;
    vbuf[2].v.ob[1] = y1;
    vbuf[2].v.ob[2] = 0;
    vbuf[2].v.flag = 0;
    vbuf[2].v.tc[0] = xuv;
    vbuf[2].v.tc[1] = 0;
    vbuf[2].v.cn[0] = 0xff;
    vbuf[2].v.cn[1] = 0xff;
    vbuf[2].v.cn[2] = 0xff;
    vbuf[2].v.cn[3] = 0xff;

    vbuf[3].v.ob[0] = x0;
    vbuf[3].v.ob[1] = y1;
    vbuf[3].v.ob[2] = 0;
    vbuf[3].v.flag = 0;
    vbuf[3].v.tc[0] = 0;
    vbuf[3].v.tc[1] = 0;
    vbuf[3].v.cn[0] = 0xff;
    vbuf[3].v.cn[1] = 0xff;
    vbuf[3].v.cn[2] = 0xff;
    vbuf[3].v.cn[3] = 0xff;

    gSPVertex(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(vbuf), 4, 0);
    gSP1Triangle(gDisplayListHead++, 0, 1, 2, 0);
    gSP1Triangle(gDisplayListHead++, 0, 2, 3, 0);
}

void render_multi_image(u8 *image, s32 x, s32 y, s32 width, s32 height, UNUSED s32 scaleX, UNUSED s32 scaleY, s32 mode) {
#if 0
    if (gPlayer1Controller->buttonPressed & L_JPAD)
        xuv += 1;
    if (gPlayer1Controller->buttonPressed & R_JPAD)
        xuv -= 1;

    print_text_fmt_int(32, 0, "%d", xuv);

    if (gPlayer1Controller->buttonPressed & U_JPAD)
        yuv += 1;
    if (gPlayer1Controller->buttonPressed & D_JPAD)
        yuv -= 1;

    print_text_fmt_int(128, 0, "%d", yuv);
#endif

    char* pool = (char*) 0x8005C000;

    s32 posW, posH, imW, imH, modeSC, mOne;
    s32 i     = 0;
    s32 num   = 256;
    s32 maskW = 1;
    s32 maskH = 1;

    gDPPipeSync(gDisplayListHead++);
    gDPSetTexturePersp(gDisplayListHead++,  G_TP_NONE);
    gDPSetCombineMode(gDisplayListHead++,   G_CC_FADEA, G_CC_FADEA);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_POINT);

    if (mode == G_CYC_COPY) {
        gDPSetCycleType( gDisplayListHead++, mode);
        gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);
        modeSC = 4;
        mOne   = 1;
    } else {
        gDPSetCycleType( gDisplayListHead++, mode);
        gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        modeSC = 1;
        mOne   = 0;
    }

    // Find how best to seperate the horizontal. Keep going until it finds a whole value.
    while (TRUE) {
        f32 val = (f32)width / (f32)num;

        if ((s32)val == val && (s32) val >= 1) {
            imW = num;
            break;
        }
        num /= 2;
        if (num == 1) {
            print_text(32, 32, "IMAGE WIDTH FAILURE");
            return;
        }
    }
    // Find the tile height
    imH = 64 / (imW / 32); // This gets the vertical amount.

    num = 2;
    // Find the width mask
    while (TRUE) {
        if ((s32) num == imW) {
            break;
        }
        num *= 2;
        maskW++;
        if (maskW == 9) {
            print_text(32, 32, "WIDTH MASK FAILURE");
            return;
        }
    }
    num = 2;
    // Find the height mask
    while (TRUE) {
        if ((s32) num == imH) {
            break;
        }
        num *= 2;
        maskH++;
        if (maskH == 9) {
            print_text(32, 32, "HEIGHT MASK FAILURE");
            return;
        }
    }
    num = height;
    // Find the height remainder
    s32 peakH  = height - (height % imH);
    s32 cycles = (width * peakH) / (imW * imH);

    // Pass 1
    for (i = 0; i < cycles; i++) {
        posW = 0;
        posH = i * imH;
        while (posH >= peakH) {
            posW += imW;
            posH -= peakH;
        }

        gDPLoadSync(gDisplayListHead++);
        gDPLoadTextureTile(gDisplayListHead++,
            image, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, height, posW, posH, ((posW + imW) - 1), ((posH + imH) - 1), 0, (G_TX_NOMIRROR | G_TX_WRAP), (G_TX_NOMIRROR | G_TX_WRAP), maskW, maskH, 0, 0);
#if 0
        gSPTextureRectangle(gDisplayListHead++,
            ((x + posW) << 2),
            ((y + posH) << 2),
            (((x + posW + imW) - mOne) << 2),
            (((y + posH + imH) - mOne) << 2),
            G_TX_RENDERTILE, 0, 0, (modeSC << 10), (1 << 10));
#else
        render_piece(&pool, x, y, posW, posH, imW, imH);
#endif
    }
    // If there's a remainder on the vertical side, then it will cycle through that too.
    if (height-peakH != 0) {
        posW = 0;
        posH = peakH;
        for (i = 0; i < (width / imW); i++) {
            posW = i * imW;
            gDPLoadSync(gDisplayListHead++);
            gDPLoadTextureTile(gDisplayListHead++,
                image, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, height, posW, posH, ((posW + imW) - 1), (height - 1), 0, (G_TX_NOMIRROR | G_TX_WRAP), (G_TX_NOMIRROR | G_TX_WRAP), maskW, maskH, 0, 0);
#if 0
            gSPTextureRectangle(gDisplayListHead++,
                (x + posW) << 2,
                (y + posH) << 2,
                ((x + posW + imW) - mOne) << 2,
                ((y + posH + imH) - mOne) << 2,
                G_TX_RENDERTILE, 0, 0, modeSC << 10, 1 << 10);
#else
        render_piece(&pool, x, y, posW, posH, imW, imH);
#endif
        }
    }

    gDPPipeSync(gDisplayListHead++);
    gDPSetTexturePersp(gDisplayListHead++,  G_TP_PERSP);
    gDPSetCombineMode(gDisplayListHead++,   G_CC_SHADE, G_CC_SHADE);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_BILERP);
}
