extern "C"
{
    #include "types.h"
    #include "game/object_list_processor.h"
    #include "game/object_helpers.h"
}
#include "ctl.h"
#include "object_fields.h"

#define oScrollCtlObject OBJECT_FIELD_OBJ(0x1b)

void onScrollStep()
{
    if (0 == gCurrentObject->oTimer)
    {    
        f32 d;
        gCurrentObject->oScrollCtlObject = obj_find_nearest_object_with_behavior((const BehaviorScript*) 0x408000, &d);
        gCurrentObject->oDrawingDistance = 10000.f;
        gCurrentObject->oHomeZ = gCurrentObject->oPosZ;
    }

    if (gCurrentObject->oScrollCtlObject)
    {
        if (gCurrentObject->oScrollCtlObject->oCtlState)
            gCurrentObject->oPosZ = -2 * gCurrentObject->oHomeZ;
        else
            gCurrentObject->oPosZ = gCurrentObject->oHomeZ;
    }
}
