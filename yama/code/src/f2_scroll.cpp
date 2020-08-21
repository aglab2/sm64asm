#include "f2_scroll.h"
extern "C"
{
    #include "game/area.h"
    #include "game/memory.h"
}

void Scroll(int x_off, int y_off, uintptr_t cmdsFlashy)
{
    char* ptr = (char*) segmented_to_virtual((void*) cmdsFlashy);

    int b1 = ptr[1];
    int b2 = ptr[2];
    int b3 = ptr[3];

    int x = ((b1 << 4) & 0xFF0) | ((b2 >> 4) & 0x00F);
    int y = ((b2 << 4) & 0xF00) | b3;

    x += x_off;
    y += y_off;

    b1 = (x & 0xFF0) >> 4;
    b2 = ((x & 0x00F) << 4) | ((y & 0xF00) >> 8);
    b3 = y & 0xFF;

    ptr[1] = b1;
    ptr[2] = b2;
    ptr[3] = b3;

}
