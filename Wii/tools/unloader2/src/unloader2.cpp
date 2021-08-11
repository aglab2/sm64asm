#include "unloader2.h"
#include "object_fields.h"
extern "C"
{
    #include "game/object_list_processor.h"
    #include "game/print.h"
    #include "engine/graph_node.h"
    #include "engine/behavior_script.h"
}

template<typename T>
static T distance(const T* x, const T* y)
{
    T ds[] = { x[0] - y[0], x[1] - y[1], x[2] - y[2] };
    return ds[0] * ds[0] + ds[1] * ds[1] + ds[2] * ds[2];
}

constexpr int cTargetDrawnCount = 50;
constexpr float cOffset = 100000.f;
constexpr float maxDistance = 1000 * cOffset;
constexpr float nextMult = 1.1f;

static int sDrawnCount = 0;
static int sNextDrawnCount = 0;
static float sCullDistance = maxDistance;

void setRenderAnimation()
{
    if (!gMarioObject)
    {
        gCurrentObject->header.gfx.node.flags |= GRAPH_RENDER_HAS_ANIMATION;
        cur_object_exec_behavior();
        return;
    }

    auto objectPos = &gCurrentObject->oPosX;
    auto marioPos = &gMarioObject->oPosX;

    auto dist = distance(objectPos, marioPos);
    if (dist > sCullDistance)
    {
        gCurrentObject->header.gfx.node.flags &= ~GRAPH_RENDER_HAS_ANIMATION;
    }
    else
    {
        sDrawnCount++;
        gCurrentObject->header.gfx.node.flags |= GRAPH_RENDER_HAS_ANIMATION;
    }

    if (dist < sCullDistance * nextMult)
    {
        sNextDrawnCount++;
    }

    cur_object_exec_behavior();
}

extern s16 gCurrLevelNum;
void recalculateDistance()
{
    if (gTimeStopState)
        return;

	int target = cTargetDrawnCount;
    sCullDistance -= (sDrawnCount - target) * cOffset / 3.f;
    sCullDistance -= (sNextDrawnCount - sDrawnCount) * cOffset / 2.f;
    if (sCullDistance > maxDistance)
        sCullDistance = maxDistance;

    // print_text_fmt_int(20, 60, "N %d", sNextDrawnCount);
    // print_text_fmt_int(20, 40, "C %d", sDrawnCount);
    // print_text_fmt_int(20, 20, "D %d", sCullDistance / cOffset);

    sDrawnCount = 0;
    sNextDrawnCount = 0;
}