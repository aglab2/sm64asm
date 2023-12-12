#include "image_select.h"
#include "render_image.h"
#include "types.h"

#include "game/game.h"

void dma_read(u8 *dest, u8 *srcStart, u8 *srcEnd);
void imageSelect()
{
    u8* romPtr = (u8 *)0x3EE0000;
    u8* ramPtr = (u8 *)0x80026000;
    u32 width = 192;
    u32 height = 128;

    static u32 sLoaded = 0;
    if (!sLoaded)
    {
        dma_read(ramPtr, romPtr, romPtr + 0x36000);
        sLoaded = 1;
    }

    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    render_multi_image(ramPtr, (320 - width) / 2, (240 - height) / 2, width * 2, height * 2, 1, 1, G_CYC_COPY);
    // -
}
