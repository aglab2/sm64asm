#include "types.h"
extern "C"
{
    #include <engine/behavior_script.h>
    #include <engine/graph_node.h>
    #include <engine/math_util.h>
    #include <game/display.h>
    #include <game/object_helpers.h>
    #include <game/rendering_graph_node.h>
    extern f32 _sqrtf(f32 x);
}

#define cur_obj_nearest_object_with_behavior obj_nearest_object_with_behavior
#define random_float RandomFloat
#define random_u16 RandomU16
#define bhvActSelector ((const BehaviorScript*) 0x13003048)

Gfx *omm_geo_star_enable_effects(s32 callContext, struct GraphNode *, int) {
    return nullptr;
}

typedef struct {
    u32 prevTimer;
    s32 counter;
    struct {
        f32 scale;
        s16 angle;
        u8 alpha;
    } rays[6];
} OmmStarGeoData;

static OmmStarGeoData sData{};

#define OMM_STAR_RAY_CYCLE 36

static inline f32 omm_sqr_f(f32 x) { return x * x; }

static struct GraphNode *omm_geo_star_get_child(struct GraphNode *node, s16 type) {
    node = node->children;
    while (node->type != type) { node = node->next; }
    return node;
}

Gfx *omm_geo_star_update_glow(s32 callContext, struct GraphNode *node, void*) {
    if (gCurGraphNodeObject && callContext == GEO_CONTEXT_RENDER) {
        struct GraphNodeTranslation *translationNode = (struct GraphNodeTranslation *) node->next;
        f32 dx = gCurGraphNodeObject->cameraToObject[0];
        f32 dy = gCurGraphNodeObject->cameraToObject[1];
        f32 dz = gCurGraphNodeObject->cameraToObject[2];
        f32 dn = _sqrtf(omm_sqr_f(dx) + omm_sqr_f(dy) + omm_sqr_f(dz));
        if (dn != 0) {
            translationNode->translation[0] = (s16) (240.f * dx / dn);
            translationNode->translation[1] = (s16) (240.f * dy / dn);
            translationNode->translation[2] = (s16) (240.f * dz / dn);
        }
    }
    return nullptr;
}

extern Gfx omm_star_ray_0_gfx[];
extern Gfx omm_star_ray_1_gfx[];
extern Gfx omm_star_ray_2_gfx[];
extern Gfx omm_star_ray_3_gfx[];
extern Gfx omm_star_ray_4_gfx[];
extern Gfx omm_star_ray_5_gfx[];

static u8* getRayEnvColor(int p)
{
    switch (p)
    {
    case 0:
    return (u8*) omm_star_ray_0_gfx + 8;
    case 1:
    return (u8*) omm_star_ray_1_gfx + 8;
    case 2:
    return (u8*) omm_star_ray_2_gfx + 8;
    case 3:
    return (u8*) omm_star_ray_3_gfx + 8;
    case 4:
    return (u8*) omm_star_ray_4_gfx + 8;
    case 5:
    return (u8*) omm_star_ray_5_gfx + 8;
    }
    return nullptr;
}

Gfx *omm_geo_star_update_ray(s32 callContext, struct GraphNode *node, void*) {
    if (gCurGraphNodeObject && callContext == GEO_CONTEXT_RENDER) {
        OmmStarGeoData *data = &sData;
        data->counter += (data->prevTimer != gGlobalTimer);
        data->prevTimer = gGlobalTimer;

        // If current tick == 0 (<=> alpha == 0), pick new random values
        struct GraphNodeGenerated *asGenerated = (struct GraphNodeGenerated *) node;
        s32 i = asGenerated->parameter;
        s32 t = (data->counter + ((OMM_STAR_RAY_CYCLE / 6) * i)) % OMM_STAR_RAY_CYCLE;
        if (t == 0) {
            data->rays[i].scale = 0.5f + (0.3f * random_float());
            data->rays[i].angle = random_u16();
            data->rays[i].alpha = 0x80 + (random_u16() & 0x7F);
        }

        // Update scale
        struct GraphNodeScale *scaleNode = (struct GraphNodeScale *) node->next;
        scaleNode->scale = data->rays[i].scale;

        // Update angle
        struct GraphNodeRotation *rotationNode = (struct GraphNodeRotation *) omm_geo_star_get_child(&scaleNode->node, GRAPH_NODE_TYPE_ROTATION);
        rotationNode->rotation[2] = data->rays[i].angle;

        // Update env color (rays color is slightly brighter)
        s32 a = data->rays[i].alpha * ((coss(0x8000 + ((0x10000 * t) / OMM_STAR_RAY_CYCLE)) + 1.f) / 2.f);
        getRayEnvColor(i)[7] = a * !cur_obj_nearest_object_with_behavior(bhvActSelector);
    }
    return nullptr;
}