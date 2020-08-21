#include "cw_scroll.h"
extern "C"
{
    #include "game/memory.h"
}

constexpr uintptr_t sLavaPalette = 0x0E07F3C0 + 4;
constexpr uintptr_t sLavaTexture = 0x0E07F3D8 + 4;

constexpr uintptr_t sQuicksandPalette = 0x0E07F770 + 4;
constexpr uintptr_t sQuicksandTexture = 0x0E07F788 + 4;

constexpr uintptr_t sPalettesStart = 0x09015820;
constexpr uintptr_t sTexturesStart = 0x09015020;

void CWScroll::Step()
{
    if (0 == oTimer % 5)
    {
        auto frame = (oTimer / 5) % 8;
        auto palette = (uintptr_t*) segmented_to_virtual((void*) sLavaPalette); 
        auto texture = (uintptr_t*) segmented_to_virtual((void*) sLavaTexture);
        *palette = sPalettesStart + 0x820 * frame;
        *texture = frame == 0 ? 0x09015018 : sTexturesStart + 0x820 * frame;
    }
    
    if (0 == oTimer % 7)
    {
        auto frame = 8 + (oTimer / 7) % 8;
        auto palette = (uintptr_t*) segmented_to_virtual((void*) sQuicksandPalette); 
        auto texture = (uintptr_t*) segmented_to_virtual((void*) sQuicksandTexture);
        *palette = sPalettesStart + 0x820 * frame;
        *texture = sTexturesStart + 0x820 * frame;
    }
};

uintptr_t CWScroll::Behavior[] = 
{
    0x08000000,
    0x0c000000, (uintptr_t) sStep,
    0x09000000,
};
