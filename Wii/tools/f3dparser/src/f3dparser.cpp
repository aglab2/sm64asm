#include "f3dparser.h"
extern "C"
{
    #include "types.h"
    #include "game/memory.h"
    #include "game/print.h"
    #include "PR/gbi.h"
}

static int distance(const Vec3s& x, const Vec3s& y)
{
    int ds[] = { x[0] - y[0], x[1] - y[1], x[2] - y[2] };
    return ds[0] * ds[0] + ds[1] * ds[1] + ds[2] * ds[2];
}

constexpr int sTarget = 4000;
constexpr auto sCopyDL = 0x80026000;

void F3DParser::CopyDL(void* from_, void* to_)
{
    u8* from = (u8*) from_;
    u64* to = (u64*) to_;
    for (; *from != 0xB8; from += 8)
    {
        *to = *(u64*) from;
        to++;
    }
    *to = *(u64*) from;
}

int F3DParser::PerformCulling(void* from_, void* to_)
{
    Vec3s marioPos = { (s16) gMarioObject->oPosX, (s16) gMarioObject->oPosY, (s16) gMarioObject->oPosZ };

    Vtx_t* vbuf;
    auto f3dptr = (u8*) from_;
    auto to = (u64*) to_;

    int leftCount = 0;
    int totalCount = 0;
    for (; *f3dptr != 0xB8; f3dptr += 8)
    {
        bool mustCopyCmd = true;

        auto cmd = *f3dptr;
        switch (cmd)
        {
        case 0x04:
            {
                // fixme improper impl
                vbuf = (Vtx_t*) segmented_to_virtual(*(void**) &f3dptr[4]);
            }
            break;
        case 0xBF:
            {
                int v[]        = { f3dptr[5] / 10, f3dptr[6] / 10, f3dptr[7] / 10 };
                Vec3s* vptrs[] = { &vbuf[v[0]].ob, &vbuf[v[1]].ob, &vbuf[v[2]].ob };

                bool canCull;
                for (int i = 0; i < 3; i++)
                {
                    canCull = distance(*vptrs[i], marioPos) > oCullDistance;
                    if (!canCull)
                        break;
                }

                totalCount++;
                if (!canCull)
                    leftCount++;

                mustCopyCmd = !canCull;
            }
        }

        if (mustCopyCmd)
        {
            *to = *(u64*) f3dptr;
            to++;
        }
    }
    
    *to = *(u64*) f3dptr;

    return leftCount;
}

void F3DParser::AdjustCulling()
{
    auto l = 0.f;
    auto r = 64000000.f;
    
    auto f3dptr = segmented_to_virtual((void*) oBehParams);
    while ((r - l) > 10000.f)
    {
        oCullDistance = (l + r) / 2.f;
        auto leftCount = PerformCulling((void*) sCopyDL, f3dptr);

        if (leftCount > sTarget)
        {
            r = oCullDistance;
        }
        else
        {
            l = oCullDistance;
        }
    }
}

void F3DParser::Init()
{
    auto f3dptr = segmented_to_virtual((void*) oBehParams);
    CopyDL(f3dptr, (void*) sCopyDL);
    AdjustCulling();
}

void F3DParser::Step()
{
    auto& marioPos = *(triplet*) &gMarioObject->oPosX;

    auto x = gMarioObject->oPosX - oPosX;
    auto y = gMarioObject->oPosY - oPosY;
    auto z = gMarioObject->oPosZ - oPosZ;

    auto dist = x*x + y*y + z*z;

    print_text_fmt_int(20, 20, "%d", dist / 10000.f);
    print_text_fmt_int(20, 40, "%d", oCullDistance / 10000.f);

    if (dist * 2 < oCullDistance)
        return;

    AdjustCulling();
    oPos = marioPos;
}

uintptr_t F3DParser::Behavior[] = {
    0x00040000,
    0x0C000000, (uintptr_t) sInit,
    0x08000000,
    0x0C000000, (uintptr_t) sStep,
    0x09000000,
};