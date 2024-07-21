#define _LANGUAGE_C

#include <game/area.h>
#include <game/display.h>
#include <game/print.h>
#include <libc/string.h>
#include <PR/os_cache.h>

typedef struct
{
    const unsigned char* buff;
    int size;
} sized_buf_t;

typedef struct
{
    void* patchAt;
    sized_buf_t repl;
    sized_buf_t orig;
} patch_t;

#define PTR_FROM_ROM_ENGINE(addr) ((void*)(addr - 0xf5580 + 0x80378800))
#define PTR_FROM_ROM_GAME(addr) ((void*)(addr + 0x80245000))
#define ARR_SIZE_ELEM(arr) { arr, sizeof(arr) / sizeof(arr[0]) }

static const unsigned char kJumpPatch[] = { 0x0C, 0x10, 0x00, 0x00 };
static const unsigned char kJumpUnpatch[] = { 0x0C, 0x0e, 0x01, 0xa4 };
static const unsigned char kJumpPatch2[] = { 0x00, 0x00, 0x20, 0x25, 0x0C, 0x0E, 0x01, 0xA4, 0x8F, 0xA5, 0x00, 0x38 };
static const unsigned char kJumpUnpatch2[] = { 0x3C, 0x01, 0x80, 0x34, 0x27, 0x28, 0x00, 0x01, 0xA4, 0x28, 0xD2, 0x78 };
static const unsigned char kVarsPatch[] = { 0x3F, 0xA9, 0x99, 0x99, 0x99, 0x99, 0x99, 0x9A, 0xBF, 0xA9, 0x99, 0x99, 0x99, 0x99, 0x99, 0x9A };
static const unsigned char kVarsUnPatch[] = { 0x3F, 0x84, 0x7A, 0xE1, 0x47, 0xAE, 0x14, 0x7B, 0xBF, 0x84, 0x7A, 0xE1, 0x47, 0xAE, 0x14, 0x7B };
static const unsigned char kGiantPatch[] = { 0x27, 0xBD, 0xFF, 0x98, 0xAF, 0xBE, 0x00, 0x40, 0xAF, 0xB7, 0x00, 0x3C, 0xAF, 0xB6, 0x00, 0x38, 0xAF, 0xB5, 0x00, 0x34, 0xAF, 0xB4, 0x00, 0x30, 0xAF, 0xB3, 0x00, 0x2C, 0xAF, 0xB2, 0x00, 0x28, 0xAF, 0xB1, 0x00, 0x24, 0xAF, 0xB0, 0x00, 0x20, 0xF7, 0xB4, 0x00, 0x18, 0x3C, 0x01, 0x40, 0x80, 0xAF, 0xBF, 0x00, 0x44, 0x44, 0x81, 0xA0, 0x00, 0x00, 0x80, 0x80, 0x25, 0x00, 0xA0, 0x98, 0x25, 0x00, 0x00, 0xF0, 0x25, 0xAC, 0x80, 0x00, 0x60, 0x00, 0x00, 0x88, 0x25, 0x24, 0x12, 0x00, 0x04, 0x27, 0xB4, 0x00, 0x5C, 0x24, 0x15, 0x00, 0x01, 0x24, 0x16, 0x00, 0x03, 0x24, 0x17, 0x00, 0x06, 0xC6, 0x04, 0x00, 0x48, 0xC6, 0x08, 0x00, 0x3C, 0x02, 0x00, 0x20, 0x25, 0x46, 0x14, 0x21, 0x83, 0x02, 0x80, 0x28, 0x25, 0x02, 0x60, 0x30, 0x25, 0x46, 0x08, 0x32, 0x80, 0xE7, 0xAA, 0x00, 0x5C, 0xC6, 0x10, 0x00, 0x4C, 0xC6, 0x04, 0x00, 0x40, 0x46, 0x14, 0x84, 0x83, 0x46, 0x04, 0x91, 0x80, 0xE7, 0xA6, 0x00, 0x60, 0xC6, 0x08, 0x00, 0x50, 0xC6, 0x10, 0x00, 0x44, 0x46, 0x14, 0x42, 0x83, 0x46, 0x10, 0x54, 0x80, 0x0C, 0x10, 0x03, 0x0F, 0xE7, 0xB2, 0x00, 0x64, 0x10, 0x40, 0x00, 0x02, 0x26, 0x31, 0x00, 0x01, 0x00, 0x40, 0xF0, 0x25, 0x50, 0x55, 0x00, 0x0A, 0xC6, 0x04, 0x00, 0x4C, 0x50, 0x56, 0x00, 0x08, 0xC6, 0x04, 0x00, 0x4C, 0x50, 0x52, 0x00, 0x06, 0xC6, 0x04, 0x00, 0x4C, 0x50, 0x57, 0x00, 0x04, 0xC6, 0x04, 0x00, 0x4C, 0x56, 0x32, 0xFF, 0xE2, 0xC6, 0x04, 0x00, 0x48, 0xC6, 0x04, 0x00, 0x4C, 0x44, 0x80, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46, 0x04, 0x30, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x45, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0xC6, 0x08, 0x00, 0x40, 0xE6, 0x08, 0x00, 0xBC, 0x0C, 0x09, 0x46, 0x2A, 0x02, 0x00, 0x20, 0x25, 0x8E, 0x0E, 0x00, 0x0C, 0x3C, 0x01, 0x10, 0x88, 0x34, 0x21, 0x08, 0x99, 0x11, 0xC1, 0x00, 0x03, 0xAE, 0x02, 0x00, 0x14, 0x0C, 0x09, 0x59, 0x87, 0x02, 0x00, 0x20, 0x25, 0x0C, 0x09, 0x5A, 0x7E, 0x02, 0x00, 0x20, 0x25, 0x8E, 0x04, 0x00, 0x88, 0x26, 0x05, 0x00, 0x3C, 0x0C, 0x0D, 0xE2, 0x00, 0x24, 0x84, 0x00, 0x20, 0x8E, 0x04, 0x00, 0x88, 0x00, 0x00, 0x28, 0x25, 0x86, 0x06, 0x00, 0x2E, 0x00, 0x00, 0x38, 0x25, 0x0C, 0x0D, 0xE2, 0x5F, 0x24, 0x84, 0x00, 0x1A, 0x8F, 0xBF, 0x00, 0x44, 0x03, 0xC0, 0x10, 0x25, 0x8F, 0xBE, 0x00, 0x40, 0xD7, 0xB4, 0x00, 0x18, 0x8F, 0xB0, 0x00, 0x20, 0x8F, 0xB1, 0x00, 0x24, 0x8F, 0xB2, 0x00, 0x28, 0x8F, 0xB3, 0x00, 0x2C, 0x8F, 0xB4, 0x00, 0x30, 0x8F, 0xB5, 0x00, 0x34, 0x8F, 0xB6, 0x00, 0x38, 0x8F, 0xB7, 0x00, 0x3C, 0x03, 0xE0, 0x00, 0x08, 0x27, 0xBD, 0x00, 0x68 };
static const unsigned char kGiantUnpatch[] = { 0x27, 0xBD, 0xFF, 0xD0, 0xAF, 0xBF, 0x00, 0x14, 0xAF, 0xA4, 0x00, 0x30, 0xAF, 0xA5, 0x00, 0x34, 0xAF, 0xA0, 0x00, 0x18, 0x8F, 0xAE, 0x00, 0x30, 0xAD, 0xC0, 0x00, 0x60, 0xAF, 0xA0, 0x00, 0x20, 0x8F, 0xAF, 0x00, 0x30, 0x3C, 0x01, 0x40, 0x80, 0x44, 0x81, 0x30, 0x00, 0xC5, 0xE4, 0x00, 0x48, 0xC5, 0xEA, 0x00, 0x3C, 0x27, 0xB8, 0x00, 0x24, 0x46, 0x06, 0x22, 0x03, 0x46, 0x0A, 0x44, 0x00, 0xE7, 0x10, 0x00, 0x00, 0x8F, 0xB9, 0x00, 0x30, 0x3C, 0x01, 0x40, 0x80, 0x44, 0x81, 0x20, 0x00, 0xC7, 0x32, 0x00, 0x4C, 0xC7, 0x28, 0x00, 0x40, 0x27, 0xA8, 0x00, 0x24, 0x46, 0x04, 0x91, 0x83, 0x46, 0x08, 0x32, 0x80, 0xE5, 0x0A, 0x00, 0x04, 0x8F, 0xA9, 0x00, 0x30, 0x3C, 0x01, 0x40, 0x80, 0x44, 0x81, 0x90, 0x00, 0xC5, 0x30, 0x00, 0x50, 0xC5, 0x26, 0x00, 0x44, 0x27, 0xAA, 0x00, 0x24, 0x46, 0x12, 0x81, 0x03, 0x46, 0x06, 0x22, 0x00, 0xE5, 0x48, 0x00, 0x08, 0x8F, 0xA4, 0x00, 0x30, 0x27, 0xA5, 0x00, 0x24, 0x0C, 0x09, 0x58, 0x2B, 0x8F, 0xA6, 0x00, 0x34, 0xAF, 0xA2, 0x00, 0x1C, 0x8F, 0xAB, 0x00, 0x1C, 0x11, 0x60, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x8F, 0xAC, 0x00, 0x1C, 0xAF, 0xAC, 0x00, 0x18, 0x8F, 0xAD, 0x00, 0x1C, 0x24, 0x01, 0x00, 0x01, 0x11, 0xA1, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x24, 0x01, 0x00, 0x03, 0x11, 0xA1, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x24, 0x01, 0x00, 0x04, 0x11, 0xA1, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x24, 0x01, 0x00, 0x06, 0x15, 0xA1, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x8F, 0xAE, 0x00, 0x20, 0x25, 0xCF, 0x00, 0x01, 0x29, 0xE1, 0x00, 0x04, 0x14, 0x20, 0xFF, 0xC8, 0xAF, 0xAF, 0x00, 0x20, 0x8F, 0xB8, 0x00, 0x30, 0x44, 0x80, 0x80, 0x00, 0xC7, 0x0A, 0x00, 0x4C, 0x46, 0x0A, 0x80, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x45, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x8F, 0xB9, 0x00, 0x30, 0xC7, 0x32, 0x00, 0x40, 0xE7, 0x32, 0x00, 0xBC, 0x0C, 0x09, 0x46, 0x2A, 0x8F, 0xA4, 0x00, 0x30, 0x8F, 0xA8, 0x00, 0x30, 0xAD, 0x02, 0x00, 0x14, 0x8F, 0xA9, 0x00, 0x30, 0x3C, 0x01, 0x10, 0x88, 0x34, 0x21, 0x08, 0x99, 0x8D, 0x2A, 0x00, 0x0C, 0x11, 0x41, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x09, 0x59, 0x87, 0x8F, 0xA4, 0x00, 0x30, 0x0C, 0x09, 0x5A, 0x7E, 0x8F, 0xA4, 0x00, 0x30, 0x8F, 0xAB, 0x00, 0x30, 0x8D, 0x64, 0x00, 0x88, 0x25, 0x65, 0x00, 0x3C, 0x0C, 0x0D, 0xE2, 0x00, 0x24, 0x84, 0x00, 0x20, 0x8F, 0xAC, 0x00, 0x30, 0x00, 0x00, 0x28, 0x25, 0x00, 0x00, 0x38, 0x25, 0x8D, 0x84, 0x00, 0x88, 0x85, 0x86, 0x00, 0x2E, 0x0C, 0x0D, 0xE2, 0x5F };
static const unsigned char kLedgePatch[] = { 0xC4, 0x8A, 0x00, 0x48, 0xC4, 0x88, 0x00, 0x3C, 0x46, 0x0A, 0x42, 0x00, 0xE7, 0xA8, 0x00, 0x28, 0xC4, 0x8A, 0x00, 0x40, 0xE7, 0xAA, 0x00, 0x2C, 0xC4, 0x92, 0x00, 0x50, 0xC4, 0x90, 0x00, 0x44, 0x46, 0x12, 0x84, 0x00, 0xE7, 0xB0, 0x00, 0x30, 0x3C, 0x01, 0x41, 0xA0 };
static const unsigned char kLedgeUnpatch[] = { 0x00, 0x00, 0x00, 0x00, 0x8F, 0xAF, 0x00, 0x50, 0xC5, 0xE8, 0x00, 0x3C, 0xE7, 0xA8, 0x00, 0x28, 0x8F, 0xB8, 0x00, 0x50, 0xC7, 0x0A, 0x00, 0x40, 0xE7, 0xAA, 0x00, 0x2C, 0x8F, 0xB9, 0x00, 0x50, 0xC7, 0x30, 0x00, 0x44, 0xE7, 0xB0, 0x00, 0x30, 0x3C, 0x01, 0x41, 0x20 };
static const unsigned char kLedgeMiniPatch[] = { 0xf0 };
static const unsigned char kLedgeMiniUnpatch[] = { 0xa0 };
static const patch_t kFrameCollisionPatch[] = {
    { PTR_FROM_ROM_ENGINE(0xfdd18) , ARR_SIZE_ELEM(kJumpPatch)     , ARR_SIZE_ELEM(kJumpUnpatch) },
    { PTR_FROM_ROM_ENGINE(0xfdd68) , ARR_SIZE_ELEM(kJumpPatch)     , ARR_SIZE_ELEM(kJumpUnpatch) },
    { PTR_FROM_ROM_ENGINE(0xfdd88) , ARR_SIZE_ELEM(kJumpPatch2)    , ARR_SIZE_ELEM(kJumpUnpatch2) },
    { PTR_FROM_ROM_ENGINE(0x108930), ARR_SIZE_ELEM(kVarsPatch)     , ARR_SIZE_ELEM(kVarsUnPatch) },
    { PTR_FROM_ROM_GAME(0x11b24)   , ARR_SIZE_ELEM(kGiantPatch)    , ARR_SIZE_ELEM(kGiantUnpatch) },
    { PTR_FROM_ROM_GAME(0x1f124)   , ARR_SIZE_ELEM(kLedgePatch)    , ARR_SIZE_ELEM(kLedgeUnpatch) },
    { PTR_FROM_ROM_GAME(0x1f223)   , ARR_SIZE_ELEM(kLedgeMiniPatch), ARR_SIZE_ELEM(kLedgeMiniUnpatch) },
    { PTR_FROM_ROM_GAME(0x1f247)   , ARR_SIZE_ELEM(kLedgeMiniPatch), ARR_SIZE_ELEM(kLedgeMiniUnpatch) },
};

void frame_collision_check()
{
    // print_text_fmt_int(20, 20, "%d", gCurrLevelNum);
    {
        static char gIsFramePatchOn = 1;
        char wantPatch = gCurrLevelNum == 14;
        if (wantPatch != gIsFramePatchOn)
        {
            for (int i = 0; i < sizeof(kFrameCollisionPatch) / sizeof(kFrameCollisionPatch[0]); i++)
            {
                const patch_t* patch = &kFrameCollisionPatch[i];
                const sized_buf_t* sb = wantPatch ? &kFrameCollisionPatch[i].repl : &kFrameCollisionPatch[i].orig;
                if (wantPatch)
                {
                    memcpy(patch->patchAt, sb->buff, sb->size);
                }
                else
                {
                    memcpy(patch->patchAt, sb->buff, sb->size);
                }
            }
            // im invalidating the whole function just in case
            osInvalICache((void*) 0x80380de8, 0x3D8);
            osInvalICache(PTR_FROM_ROM_GAME(0x11b24), 0x1B4);
            osInvalICache((void*) 0x802460fc, 0x1B8);
            osInvalDCache(PTR_FROM_ROM_ENGINE(0x108930), 0x10);
            gIsFramePatchOn = wantPatch;
        }
    }
    {
        static char gIsQSLGPatchOn = 1;
        char wantPatch = gCurrLevelNum == 9;
        if (wantPatch != gIsQSLGPatchOn)
        {
            if (wantPatch)
            {
                *(unsigned int*)(PTR_FROM_ROM_GAME(0x1A888)) = 0x08103D80U;
                *(unsigned int*)(PTR_FROM_ROM_GAME(0x1A88C)) = 0;
            }
            else
            {
                *(unsigned int*)(PTR_FROM_ROM_GAME(0x1A888)) = 0x2405054CU;
                *(unsigned int*)(PTR_FROM_ROM_GAME(0x1A88C)) = 0x0C094B3DU;
            }

            osInvalICache((void*) 0x8025f6c0, 0x2B0);
            gIsQSLGPatchOn = wantPatch;
        }
    }
    {
        static char gIsRedmatPatchOn = 1;
        char wantPatch = gCurrLevelNum == 15;
        if (wantPatch != gIsRedmatPatchOn)
        {
            if (wantPatch)
            {
                *(unsigned int*)(PTR_FROM_ROM_GAME(0x861CC)) = 0x0c101800;
            }
            else
            {
                *(unsigned int*)(PTR_FROM_ROM_GAME(0x861CC)) = 0x0c101847;
            }

            osInvalICache(PTR_FROM_ROM_GAME(0x861c0), 0x20);
            gIsRedmatPatchOn = wantPatch;
        }
    }
}