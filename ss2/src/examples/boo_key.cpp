#include "boo_key.h"
extern "C"
{
    #include "game/object_helpers.h"
}
#include "object_fields.h"

void BooKey::Init()
{
    auto key = spawn_object(this, 0xf2, (const BehaviorScript*) 0x408018);
    key->oBehParams = oBehParams;
    key->oFaceAngleYaw = 0x4000;
}

uintptr_t BooKey::Behavior[] = 
{
    0x102F0001,
    0x11012049,
    0x10050000,
    0x2D000000,
    0x103E0002,
    0x23000000, 0x008C0050,
    0x2E000000, 0x0028003C,
    0x0E15001E,
    0x0C000000, 0x802A4120,
    0x0C000000, (uintptr_t) sInit,
    0x30000000, 0x001E0000, 0xFFCE03E8, 0x03E800F2, 0x00000000,
    0x0C000000, 0x802C3440,
    0x08000000,
    0x0C000000, 0x802C4824,
    0x09000000,
};