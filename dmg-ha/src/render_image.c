
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

static Gfx* gRenderImageGfxPool;
static void render_piece(char** pool, int x, int y, int posW, int posH, int imW, int imH, int scale)
{
    const int xoff = -15;
    const int yoff = 352;

    int x0 = xoff + (x + posW);
    int y0 = yoff - (y + posH);
    
    int x1 = xoff + (x + posW) + imW;
    int y1 = yoff - (y + posH) + imH;

    f32 fscale = 1.5f * scale;
    x0 /= fscale;
    x1 /= fscale;
    y0 /= fscale;
    y1 /= fscale;

    if (scale != 1)
    {
        x0 += 190;
        y0 += 70;
        x1 += 190;
        y1 += 70;
    }

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

    gSPVertex(gRenderImageGfxPool++, VIRTUAL_TO_PHYSICAL(vbuf), 4, 0);
    gSP1Triangle(gRenderImageGfxPool++, 0, 1, 2, 0);
    gSP1Triangle(gRenderImageGfxPool++, 0, 2, 3, 0);
}

#define	gDPLoadTextureBlock2(pkt, timg, fmt, siz, width, height,		\
		uls, ult, lrs, lrt, pal,				\
		cms, cmt, masks, maskt, shifts, shiftt)			\
{									\
	gDPSetTextureImage(pkt, fmt, siz##_LOAD_BLOCK, 1, timg);	\
	gDPSetTile(pkt, fmt, siz,					\
		(((((lrs)-(uls)+1) * siz##_TILE_BYTES)+7)>>3), 0,	\
		G_TX_LOADTILE, 0 , cmt, maskt, shiftt, cms, masks,	\
		shifts);						\
	gDPLoadSync(pkt);						\
	gDPLoadBlock(pkt, G_TX_LOADTILE, \
			(uls)<<G_TEXTURE_IMAGE_FRAC,			\
			(ult)<<G_TEXTURE_IMAGE_FRAC,			\
			(lrs)<<G_TEXTURE_IMAGE_FRAC,			\
			(lrt)<<G_TEXTURE_IMAGE_FRAC);			\
	gDPPipeSync(pkt);						\
	gDPSetTile(pkt, fmt, siz,					\
		(((((lrs)-(uls)+1) * siz##_LINE_BYTES)+7)>>3), 0,	\
		G_TX_RENDERTILE, pal, cmt, maskt, shiftt, cms, masks,	\
		shifts);						\
	gDPSetTileSize(pkt, G_TX_RENDERTILE,				\
			(uls)<<G_TEXTURE_IMAGE_FRAC,			\
			(ult)<<G_TEXTURE_IMAGE_FRAC,			\
			(lrs)<<G_TEXTURE_IMAGE_FRAC,			\
			(lrt)<<G_TEXTURE_IMAGE_FRAC)			\
}

void render_multi_image(Gfx** dlGfx, u8 *image, s32 x, s32 y, s32 width, s32 height, s32 scaleX, UNUSED s32 scaleY, s32 mode) {
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

    gRenderImageGfxPool = (Gfx*) (0x80026000 + 0x30000);
    char* pool = (char*) 0x8005C000;

    s32 posW, posH, imW, imH, modeSC, mOne;
    s32 i     = 0;
    s32 num   = 256;
    s32 maskW = 1;
    s32 maskH = 1;

    gDPPipeSync(gRenderImageGfxPool++);
    gDPSetTexturePersp(gRenderImageGfxPool++,  G_TP_NONE);
    gDPSetCombineMode(gRenderImageGfxPool++,   G_CC_FADEA, G_CC_FADEA);
    gDPSetTextureFilter(gRenderImageGfxPool++, G_TF_POINT);

    if (mode == G_CYC_COPY) {
        gDPSetCycleType( gRenderImageGfxPool++, mode);
        gDPSetRenderMode(gRenderImageGfxPool++, G_RM_NOOP, G_RM_NOOP2);
        modeSC = 4;
        mOne   = 1;
    } else {
        gDPSetCycleType( gRenderImageGfxPool++, mode);
        gDPSetRenderMode(gRenderImageGfxPool++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
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
            // print_text(32, 32, "IMAGE WIDTH FAILURE");
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
            // print_text(32, 32, "WIDTH MASK FAILURE");
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
            // print_text(32, 32, "HEIGHT MASK FAILURE");
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

        gDPLoadSync(gRenderImageGfxPool++);
        gDPLoadTextureTile(gRenderImageGfxPool++,
            image, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, height, posW, posH, ((posW + imW) - 1), ((posH + imH) - 1), 0, (G_TX_NOMIRROR | G_TX_WRAP), (G_TX_NOMIRROR | G_TX_WRAP), maskW, maskH, 0, 0);
#if 0
        gSPTextureRectangle(gRenderImageGfxPool++,
            ((x + posW) << 2),
            ((y + posH) << 2),
            (((x + posW + imW) - mOne) << 2),
            (((y + posH + imH) - mOne) << 2),
            G_TX_RENDERTILE, 0, 0, (modeSC << 10), (1 << 10));
#else
        render_piece(&pool, x, y, posW, posH, imW, imH, scaleX);
#endif
    }
    // If there's a remainder on the vertical side, then it will cycle through that too.
    if (height-peakH != 0) {
        posW = 0;
        posH = peakH;
        for (i = 0; i < (width / imW); i++) {
            posW = i * imW;
            gDPLoadSync(gRenderImageGfxPool++);
            gDPLoadTextureTile(gRenderImageGfxPool++,
                image, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, height, posW, posH, ((posW + imW) - 1), (height - 1), 0, (G_TX_NOMIRROR | G_TX_WRAP), (G_TX_NOMIRROR | G_TX_WRAP), maskW, maskH, 0, 0);
#if 0
            gSPTextureRectangle(gRenderImageGfxPool++,
                (x + posW) << 2,
                (y + posH) << 2,
                ((x + posW + imW) - mOne) << 2,
                ((y + posH + imH) - mOne) << 2,
                G_TX_RENDERTILE, 0, 0, modeSC << 10, 1 << 10);
#else
        render_piece(&pool, x, y, posW, posH, imW, imH, scaleX);
#endif
        }
    }

    gDPPipeSync(gRenderImageGfxPool++);
    gDPSetTexturePersp(gRenderImageGfxPool++,  G_TP_PERSP);
    gDPSetCombineMode(gRenderImageGfxPool++,   G_CC_SHADE, G_CC_SHADE);
    gDPSetTextureFilter(gRenderImageGfxPool++, G_TF_BILERP);
    gSPEndDisplayList(gRenderImageGfxPool++);

    gSPDisplayList((*dlGfx)++, 0x0026000 + 0x30000);
}
