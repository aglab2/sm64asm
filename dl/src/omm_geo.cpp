#include "omm.h"

#include "types.h"

#include <geo_commands.h>

extern Gfx *omm_geo_star_enable_effects(s32 callContext, struct GraphNode *node, int context);
extern Gfx *omm_geo_star_update_ray(s32 callContext, struct GraphNode *node, void* context);
extern Gfx *omm_geo_star_update_glow(s32 callContext, struct GraphNode *node, void* context);

static const Vtx omm_star_rays_vertices[] = {
    { { { (short) 0.000000, (short) 0.000000, (short) 0.000000 }, 0, { 0, 0 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { (short) 1198.554565, (short) 58.881210, (short) 0.000000 }, 0, { 0, 0 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { (short) 1198.554565, (short) -58.881210, (short) 0.000000 }, 0, { 0, 0 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { (short) 0.000000, (short) 0.000000, (short) 0.000000 }, 0, { 0, 0 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { (short) 1196.748535, (short) 88.277481, (short) 0.000000 }, 0, { 0, 0 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { (short) 1196.748535, (short) -88.277481, (short) 0.000000 }, 0, { 0, 0 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { (short) 0.000000, (short) 0.000000, (short) 0.000000 }, 0, { 0, 0 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { (short) 1194.221680, (short) 117.620567, (short) 0.000000 }, 0, { 0, 0 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { (short) 1194.221680, (short) -117.620567, (short) 0.000000 }, 0, { 0, 0 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { (short) 0.000000, (short) 0.000000, (short) 0.000000 }, 0, { 0, 0 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { (short) 1190.975464, (short) 146.892807, (short) 0.000000 }, 0, { 0, 0 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { (short) 1190.975464, (short) -146.892807, (short) 0.000000 }, 0, { 0, 0 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { (short) 0.000000, (short) 0.000000, (short) 0.000000 }, 0, { 0, 0 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { (short) 1187.011841, (short) 176.076569, (short) 0.000000 }, 0, { 0, 0 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { (short) 1187.011841, (short) -176.076569, (short) 0.000000 }, 0, { 0, 0 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { (short) 0.000000, (short) 0.000000, (short) 0.000000 }, 0, { 0, 0 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { (short) 1182.333130, (short) 205.154266, (short) 0.000000 }, 0, { 0, 0 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { (short) 1182.333130, (short) -205.154266, (short) 0.000000 }, 0, { 0, 0 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
};

const Gfx omm_star_ray_0_triangles[] = {
    gsSPVertex(VIRTUAL_TO_PHYSICAL2(omm_star_rays_vertices + 0), 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 1, 0),
    gsSPEndDisplayList(),
};

static const Gfx omm_star_ray_1_triangles[] = {
    gsSPVertex(VIRTUAL_TO_PHYSICAL2(omm_star_rays_vertices + 3), 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 1, 0),
    gsSPEndDisplayList(),
};

static const Gfx omm_star_ray_2_triangles[] = {
    gsSPVertex(VIRTUAL_TO_PHYSICAL2(omm_star_rays_vertices + 6), 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 1, 0),
    gsSPEndDisplayList(),
};

static const Gfx omm_star_ray_3_triangles[] = {
    gsSPVertex(VIRTUAL_TO_PHYSICAL2(omm_star_rays_vertices + 9), 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 1, 0),
    gsSPEndDisplayList(),
};

static const Gfx omm_star_ray_4_triangles[] = {
    gsSPVertex(VIRTUAL_TO_PHYSICAL2(omm_star_rays_vertices + 12), 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 1, 0),
    gsSPEndDisplayList(),
};

static const Gfx omm_star_ray_5_triangles[] = {
    gsSPVertex(VIRTUAL_TO_PHYSICAL2(omm_star_rays_vertices + 15), 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 1, 0),
    gsSPEndDisplayList(),
};

Gfx omm_star_ray_0_gfx[] = {
    gsDPPipeSync(),
    gsDPSetEnvColor(0xad, 0xd8, 0xe6, 0xFF),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineLERP(SHADE, 0, ENVIRONMENT, 0, SHADE, 0, ENVIRONMENT, 0, SHADE, 0, ENVIRONMENT, 0, SHADE, 0, ENVIRONMENT, 0),
    gsSPDisplayList(VIRTUAL_TO_PHYSICAL2(omm_star_ray_0_triangles)),
    gsSPSetGeometryMode(G_LIGHTING),
    gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE),
    gsDPSetEnvColor(0xFF, 0xFF, 0xFF, 0xFF),
    gsSPEndDisplayList(),
};

Gfx omm_star_ray_1_gfx[] = {
    gsDPPipeSync(),
    gsDPSetEnvColor(0xad, 0xd8, 0xe6, 0xFF),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineLERP(SHADE, 0, ENVIRONMENT, 0, SHADE, 0, ENVIRONMENT, 0, SHADE, 0, ENVIRONMENT, 0, SHADE, 0, ENVIRONMENT, 0),
    gsSPDisplayList(VIRTUAL_TO_PHYSICAL2(omm_star_ray_1_triangles)),
    gsSPSetGeometryMode(G_LIGHTING),
    gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE),
    gsDPSetEnvColor(0xFF, 0xFF, 0xFF, 0xFF),
    gsSPEndDisplayList(),
};

Gfx omm_star_ray_2_gfx[] = {
    gsDPPipeSync(),
    gsDPSetEnvColor(0xad, 0xd8, 0xe6, 0xFF),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineLERP(SHADE, 0, ENVIRONMENT, 0, SHADE, 0, ENVIRONMENT, 0, SHADE, 0, ENVIRONMENT, 0, SHADE, 0, ENVIRONMENT, 0),
    gsSPDisplayList(VIRTUAL_TO_PHYSICAL2(omm_star_ray_2_triangles)),
    gsSPSetGeometryMode(G_LIGHTING),
    gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE),
    gsDPSetEnvColor(0xFF, 0xFF, 0xFF, 0xFF),
    gsSPEndDisplayList(),
};

Gfx omm_star_ray_3_gfx[] = {
    gsDPPipeSync(),
    gsDPSetEnvColor(0xad, 0xd8, 0xe6, 0xFF),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineLERP(SHADE, 0, ENVIRONMENT, 0, SHADE, 0, ENVIRONMENT, 0, SHADE, 0, ENVIRONMENT, 0, SHADE, 0, ENVIRONMENT, 0),
    gsSPDisplayList(VIRTUAL_TO_PHYSICAL2(omm_star_ray_3_triangles)),
    gsSPSetGeometryMode(G_LIGHTING),
    gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE),
    gsDPSetEnvColor(0xFF, 0xFF, 0xFF, 0xFF),
    gsSPEndDisplayList(),
};

Gfx omm_star_ray_4_gfx[] = {
    gsDPPipeSync(),
    gsDPSetEnvColor(0xad, 0xd8, 0xe6, 0xFF),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineLERP(SHADE, 0, ENVIRONMENT, 0, SHADE, 0, ENVIRONMENT, 0, SHADE, 0, ENVIRONMENT, 0, SHADE, 0, ENVIRONMENT, 0),
    gsSPDisplayList(VIRTUAL_TO_PHYSICAL2(omm_star_ray_4_triangles)),
    gsSPSetGeometryMode(G_LIGHTING),
    gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE),
    gsDPSetEnvColor(0xFF, 0xFF, 0xFF, 0xFF),
    gsSPEndDisplayList(),
};

Gfx omm_star_ray_5_gfx[] = {
    gsDPPipeSync(),
    gsDPSetEnvColor(0xad, 0xd8, 0xe6, 0xFF),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineLERP(SHADE, 0, ENVIRONMENT, 0, SHADE, 0, ENVIRONMENT, 0, SHADE, 0, ENVIRONMENT, 0, SHADE, 0, ENVIRONMENT, 0),
    gsSPDisplayList(VIRTUAL_TO_PHYSICAL2(omm_star_ray_5_triangles)),
    gsSPSetGeometryMode(G_LIGHTING),
    gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE),
    gsDPSetEnvColor(0xFF, 0xFF, 0xFF, 0xFF),
    gsSPEndDisplayList(),
};

static const GeoLayout omm_geo_star_effects[] = {
    GEO_ASM(0, omm_geo_star_enable_effects),
    GEO_SCALE(0, 0x10000),
    GEO_OPEN_NODE(),
        GEO_SCALE(0, 0x4000),
        GEO_OPEN_NODE(),
            GEO_OPEN_NODE(),
                GEO_ASM(0, omm_geo_star_update_glow),
                GEO_TRANSLATE_NODE(0, 0, 0, 0),
                GEO_OPEN_NODE(),
                    GEO_DISPLAY_LIST(5, 0x4082690),
                GEO_CLOSE_NODE(),
            GEO_CLOSE_NODE(),
            GEO_OPEN_NODE(),
                GEO_ASM(0, omm_geo_star_update_ray),
                GEO_SCALE(0, 0x10000),
                GEO_OPEN_NODE(),
                    GEO_ROTATION_NODE(0, 0, 0, 0),
                    GEO_OPEN_NODE(),
                        GEO_DISPLAY_LIST(5, VIRTUAL_TO_PHYSICAL2(omm_star_ray_0_gfx)),
                    GEO_CLOSE_NODE(),
                GEO_CLOSE_NODE(),
            GEO_CLOSE_NODE(),
            GEO_OPEN_NODE(),
                GEO_ASM(1, omm_geo_star_update_ray),
                GEO_SCALE(0, 0x10000),
                GEO_OPEN_NODE(),
                    GEO_ROTATION_NODE(0, 0, 0, 0),
                    GEO_OPEN_NODE(),
                        GEO_DISPLAY_LIST(5, VIRTUAL_TO_PHYSICAL2(omm_star_ray_1_gfx)),
                    GEO_CLOSE_NODE(),
                GEO_CLOSE_NODE(),
            GEO_CLOSE_NODE(),
            GEO_OPEN_NODE(),
                GEO_ASM(2, omm_geo_star_update_ray),
                GEO_SCALE(0, 0x10000),
                GEO_OPEN_NODE(),
                    GEO_ROTATION_NODE(0, 0, 0, 0),
                    GEO_OPEN_NODE(),
                        GEO_DISPLAY_LIST(5, VIRTUAL_TO_PHYSICAL2(omm_star_ray_2_gfx)),
                    GEO_CLOSE_NODE(),
                GEO_CLOSE_NODE(),
            GEO_CLOSE_NODE(),
            GEO_OPEN_NODE(),
                GEO_ASM(3, omm_geo_star_update_ray),
                GEO_SCALE(0, 0x10000),
                GEO_OPEN_NODE(),
                    GEO_ROTATION_NODE(0, 0, 0, 0),
                    GEO_OPEN_NODE(),
                        GEO_DISPLAY_LIST(5, VIRTUAL_TO_PHYSICAL2(omm_star_ray_3_gfx)),
                    GEO_CLOSE_NODE(),
                GEO_CLOSE_NODE(),
            GEO_CLOSE_NODE(),
            GEO_OPEN_NODE(),
                GEO_ASM(4, omm_geo_star_update_ray),
                GEO_SCALE(0, 0x10000),
                GEO_OPEN_NODE(),
                    GEO_ROTATION_NODE(0, 0, 0, 0),
                    GEO_OPEN_NODE(),
                        GEO_DISPLAY_LIST(5, VIRTUAL_TO_PHYSICAL2(omm_star_ray_4_gfx)),
                    GEO_CLOSE_NODE(),
                GEO_CLOSE_NODE(),
            GEO_CLOSE_NODE(),
            GEO_OPEN_NODE(),
                GEO_ASM(5, omm_geo_star_update_ray),
                GEO_SCALE(0, 0x10000),
                GEO_OPEN_NODE(),
                    GEO_ROTATION_NODE(0, 0, 0, 0),
                    GEO_OPEN_NODE(),
                        GEO_DISPLAY_LIST(5, VIRTUAL_TO_PHYSICAL2(omm_star_ray_5_gfx)),
                    GEO_CLOSE_NODE(),
                GEO_CLOSE_NODE(),
            GEO_CLOSE_NODE(),
        GEO_CLOSE_NODE(),
    GEO_CLOSE_NODE(),
    GEO_RETURN(),
};

const GeoLayout star_geo[] = {
   GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0x9B, 100),
   GEO_OPEN_NODE(),
      GEO_SCALE(0x00, 16384),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(4, 0x0302BA18),
         GEO_DISPLAY_LIST(1, 0x04081e00),
      GEO_CLOSE_NODE(),
      GEO_OPEN_NODE(),
        GEO_BILLBOARD(),
        GEO_OPEN_NODE(),
            GEO_BRANCH(1, VIRTUAL_TO_PHYSICAL2(omm_geo_star_effects)),
        GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
