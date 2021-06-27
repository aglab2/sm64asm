extern "C"
{
    #include "types.h"
    #include "game/object_list_processor.h"
    #include "game/object_helpers.h"
}
#include "ctl.h"
#include "object_fields.h"

#define oSecretCtlObject OBJECT_FIELD_OBJ(0x1b)

void onSecretStep()
{
    if (0 == gCurrentObject->oTimer)
    {    
        f32 d;
        gCurrentObject->oSecretCtlObject = obj_find_nearest_object_with_behavior((const BehaviorScript*) 0x408000, &d);
        gCurrentObject->oDrawingDistance = 10000.f;
    }

    int speed = 0x69 * 6;
    if (gCurrentObject->oSecretCtlObject)
    {
        if (gCurrentObject->oSecretCtlObject->oCtlState)
            speed = -2 * speed;
    }

    gCurrentObject->oFaceAngleYaw += speed;
}
