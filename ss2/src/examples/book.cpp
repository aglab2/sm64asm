#include "book.h"
extern "C"
{
    #include "audio/external.h"
    #include "audio_defines.h"
    #include "game/object_helpers.h"
    #include "model_ids.h"
}
#include "bookshelf.h"
#include "obj_ctl.h"

constexpr float bookStepOff = 60.f;

void Book::Init()
{
    scale_object(this, 1.5f);
    oBookPushed = false;
    oBookOther = obj_nearest_object_with_behavior((const BehaviorScript*) (0x408030));
    oBookBookShelf = obj_nearest_object_with_behavior((const BehaviorScript*) (0x408000));
}

void Book::Step()
{
    if (oBookBookShelf->oBookShelfBookCount == 0)
    {
        oPosZ += 10.f;
        if (oPosZ > 5000.f)
        {
            activeFlags = 0;
        }
        return;
    }

    if (oBookPushed)
        return;
    
    auto marioPos = *(triplet*) &gMarioObject->oPosX;
    marioPos.y += 100.f;
    auto dist = marioPos.Distance(oPos);

    if (dist < 100.f)
    {
        play_sound(SOUND_MENU_CAMERA_BUZZ, gDefaultSoundArgs);
        ObjectCtl::SpawnParticlesAt(this);

        oBookBookShelf->oBookShelfBookCount--;
        oBookPushed = true;
        oPosX -= bookStepOff;

        if (!oBehParams2ndByte && oBookOther->oBookPushed)
        {
            oBookBookShelf->oBookShelfBookCount++;
            ObjectCtl::SpawnParticlesAt(oBookOther);
            oBookOther->oBookPushed = false;
            oBookOther->oPosX += bookStepOff;
        }
    }
}

uintptr_t Book::Behavior[] = {
    0x11010001,
    0x0c000000, (uintptr_t) sInit,
    0x08000000,
    0x0c000000, (uintptr_t) sStep,
    0x09000000,
};