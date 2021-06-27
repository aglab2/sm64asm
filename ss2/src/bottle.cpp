#include "bottle.h"
extern "C"
{
    #include "game/level_update.h"
    #include "game/object_helpers.h"
    #include "game/memory.h"
    #include "engine/math_util.h"
    #include "PR/gbi.h"
}
#include "ctl.h"

/*
[012830B8 / 09018FB8] 04 A0 00 B0 09 01 86 C0 // Load 11 vertices from address 0x090186C0
[012830C0 / 09018FC0] BF 00 00 00 00 00 0A 14 // Draw triangle using vertices (0,1,2)
[012830C8 / 09018FC8] BF 00 00 00 00 0A 00 1E // Draw triangle using vertices (1,0,3)
[012830D0 / 09018FD0] BF 00 00 00 00 28 32 3C // Draw triangle using vertices (4,5,6)
[012830D8 / 09018FD8] BF 00 00 00 00 32 28 46 // Draw triangle using vertices (5,4,7)
[012830E0 / 09018FE0] BF 00 00 00 00 50 5A 64 // Draw triangle using vertices (8,9,10)
[012830E8 / 09018FE8] 04 A0 00 B0 09 01 87 70 // Load 11 vertices from address 0x09018770
[012830F0 / 09018FF0] BF 00 00 00 00 00 0A 14 // Draw triangle using vertices (0,1,2)
[012830F8 / 09018FF8] BF 00 00 00 00 1E 28 32 // Draw triangle using vertices (3,4,5)
[01283100 / 09019000] BF 00 00 00 00 28 1E 3C // Draw triangle using vertices (4,3,6)
[01283108 / 09019008] BF 00 00 00 00 46 50 5A // Draw triangle using vertices (7,8,9)
[01283110 / 09019010] BF 00 00 00 00 50 46 64 // Draw triangle using vertices (8,7,10)
[01283118 / 09019018] 04 A0 00 B0 09 01 88 20 // Load 11 vertices from address 0x09018820
[01283120 / 09019020] BF 00 00 00 00 00 0A 14 // Draw triangle using vertices (0,1,2)
[01283128 / 09019028] BF 00 00 00 00 14 0A 1E // Draw triangle using vertices (2,1,3)
[01283130 / 09019030] BF 00 00 00 00 28 32 3C // Draw triangle using vertices (4,5,6)
[01283138 / 09019038] BF 00 00 00 00 32 28 46 // Draw triangle using vertices (5,4,7)
[01283140 / 09019040] BF 00 00 00 00 50 5A 64 // Draw triangle using vertices (8,9,10)
[01283148 / 09019048] 04 80 00 90 09 01 88 D0 // Load 9 vertices from address 0x090188D0
[01283150 / 09019050] BF 00 00 00 00 00 0A 14 // Draw triangle using vertices (0,1,2)
[01283158 / 09019058] BF 00 00 00 00 00 1E 0A // Draw triangle using vertices (0,3,1)
[01283160 / 09019060] BF 00 00 00 00 1E 00 28 // Draw triangle using vertices (3,0,4)
[01283168 / 09019068] BF 00 00 00 00 32 3C 46 // Draw triangle using vertices (5,6,7)
[01283170 / 09019070] BF 00 00 00 00 3C 32 50 // Draw triangle using vertices (6,5,8)

09018FB8 = 012830B8
090186C0 = 012827C0

090186C0 26 vertices
00 21 00 14 FF C6 00 00 04 B0 0A A8 6E 00 C0 FF 
00 43 01 00 00 00 00 00 05 80 0C 0E 6E 00 C0 FF 
00 43 00 14 00 00 00 00 05 80 0C 0E 6E 00 C0 FF 
00 21 01 00 FF C6 00 00 04 B0 0A A8 6E 00 C0 FF 
00 21 00 14 FF C6 00 00 04 B0 0A A8 00 00 81 FF 
FF DF 01 00 FF C6 00 00 03 12 0A A8 00 00 81 FF 
00 21 01 00 FF C6 00 00 04 B0 0A A8 00 00 81 FF 
FF DF 00 14 FF C6 00 00 03 12 0A A8 00 00 81 FF 
FF DF 00 14 00 3A 00 00 03 12 0D 76 00 81 00 FF 
FF DF 00 14 FF C6 00 00 03 12 0A A8 00 81 00 FF 
00 21 00 14 FF C6 00 00 04 B0 0A A8 00 81 00 FF 
FF DF 00 14 FF C6 00 00 03 12 0A A8 00 81 00 FF 
FF DF 00 14 00 3A 00 00 03 12 0D 76 00 81 00 FF 
FF BD 00 14 00 00 00 00 02 42 0C 0E 00 81 00 FF 
FF DF 00 14 00 3A 00 00 03 12 0D 76 92 00 40 FF 
FF BD 01 00 00 00 00 00 02 42 0C 0E 92 00 40 FF 
FF BD 00 14 00 00 00 00 02 42 0C 0E 92 00 40 FF 
FF DF 01 00 00 3A 00 00 03 12 0D 76 92 00 40 FF 
FF DF 00 14 00 3A 00 00 03 12 0D 76 00 00 7F FF 
00 21 01 00 00 3A 00 00 04 B0 0D 76 00 00 7F FF 
FF DF 01 00 00 3A 00 00 03 12 0D 76 00 00 7F FF 
00 21 00 14 00 3A 00 00 04 B0 0D 76 00 00 7F FF 
FF DF 00 14 00 3A 00 00 03 12 0D 76 00 81 00 FF 
00 21 00 14 FF C6 00 00 04 B0 0A A8 00 81 00 FF 
00 21 00 14 00 3A 00 00 04 B0 0D 76 00 81 00 FF 
00 43 00 14 00 00 00 00 05 80 0C 0E 00 81 00 FF

MinY = 0x14
MaxY = 0x100
 */

void Bottle::Init()
{
    f32 d;
    oBottleCtlObject = obj_find_nearest_object_with_behavior((const BehaviorScript*) 0x408000, &d);
    oDrawingDistance = 10000.f;
}

void Bottle::Step()
{
    obj_scale(0.3f);
    oPos = (*(triplet*) &gMarioObject->oPosX);
    oPosX += 30 * sins(0xC000 + gMarioObject->oFaceAngleYaw);
    oPosY += 130;
    oPosZ += 30 * coss(0xC000 + gMarioObject->oFaceAngleYaw);;
    
    oFaceAngleYaw += 0x69;
    if (!oBottleCtlObject->oCtlHealTimer)
    {
        obj_disable_rendering();
    }
    else
    {
        int size = oBottleCtlObject->oCtlHealTimer > 118 ? 118 : oBottleCtlObject->oCtlHealTimer;

        obj_enable_rendering();
        obj_unhide();
        Vtx_t* vtx = (Vtx_t*) segmented_to_virtual((void*) 0x090186C0);
        for (int i = 0; i < 42; i++)
        {
            if (vtx->ob[1] != 0x14)
            {
                vtx->ob[1] = 0x14 + 2 * size;
            }
            vtx++;
        }
    }
}

uintptr_t Bottle::Behavior[] = 
{
    0x11010001,
    0x0C000000, (uintptr_t) sInit,
    0x08000000,
    0x0C000000, (uintptr_t) sStep,
    0x09000000,
};