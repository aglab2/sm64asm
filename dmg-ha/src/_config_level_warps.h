static const char sLevelWarpLevels[] = {
    LevelConv_PlainLevels_C1,
    LevelConv_PlainLevels_C2,
    LevelConv_PlainLevels_S2,
    LevelConv_PlainLevels_C3,
    LevelConv_PlainLevels_C4,
    LevelConv_PlainLevels_C15,
    LevelConv_PlainLevels_C5,
    LevelConv_PlainLevels_C6,
    LevelConv_PlainLevels_C7,
    LevelConv_PlainLevels_C8,
    LevelConv_PlainLevels_C9,
    LevelConv_PlainLevels_C10,
    // LevelConv_PlainLevels_C11,
    LevelConv_PlainLevels_C12,
    LevelConv_PlainLevels_C13,
    // LevelConv_PlainLevels_C14,

    LevelConv_PlainLevels_B1,
    LevelConv_PlainLevels_B2,
    // LevelConv_PlainLevels_B3,

    LevelConv_PlainLevels_Slide,

    LevelConv_PlainLevels_MC,
    LevelConv_PlainLevels_WC,
    LevelConv_PlainLevels_VC,

    LevelConv_PlainLevels_S1,
    // LevelConv_PlainLevels_S3,

    // extras, currently 3 courses
    LevelConv_PlainLevels_F1,
    LevelConv_PlainLevels_F2,
    // LevelConv_PlainLevels_F3,

    LevelConv_PlainLevels_OW1,
    LevelConv_PlainLevels_OW2,
    LevelConv_PlainLevels_OW3,
};

#define USTR_DASH 0x9f
#define USTR_SPACE 0x9E

// Game does not store names for each extra course (fights currently), so we define them here.
static const u8 uAndrewSM64[] = { 0x0A, 0x17, 0x0D, 0x1B, 0x0E, 0x20, 0x1C, 0x16, 0x06, 0x04, 0xFF };
static const u8 uBowser1Fight[] = { 0X0B, 0x18, 0x20, 0x1C, 0x0E, 0x1B, 0x9E, 0x01, 0x9E, 0x0F, 0x12, 0x10, 0x11, 0x1D, 0xFF };
static const u8 uBowser2Fight[] = { 0X0B, 0x18, 0x20, 0x1C, 0x0E, 0x1B, 0x9E, 0x02, 0x9E, 0x0F, 0x12, 0x10, 0x11, 0x1D, 0xFF };
static const u8 uBowser3Fight[] = { 0X0B, 0x18, 0x20, 0x1C, 0x0E, 0x1B, 0x9E, 0x03, 0x9E, 0x0F, 0x12, 0x10, 0x11, 0x1D, 0xFF };
static const u8 uOW1[] = { 0x1C, 0x1D, 0x18, 0x16, 0x19, 0x12, 0x17, 0x10, 0x9E, 0x10, 0x1B, 0x18, 0x1E, 0x17, 0x0D, 0x1C, 0xFF }; // Stomping Grounds
static const u8 uOW2[] = { 0x1B, 0x18, 0x0C, 0x14, 0x0E, 0x1D, 0x19, 0x1E, 0x17, 0x0C, 0x11, 0x9E, 0x16, 0x0A, 0x15, 0x15, 0xFF }; // Rocketpunch Mall
static const u8 uOW3[] = { 0x16, 0x1E, 0x1C, 0x12, 0x0C, 0x0A, 0x15, 0x9E, 0x0C, 0x15, 0x12, 0x0F, 0x0F, 0x1C, 0xFF }; // Musical Cliffs
static const u8 uEnding[] = { 0x0E, 0x17, 0x0D, 0x12, 0x17, 0x10, 0xFF };
static const u8 uMC[] = { 0x16, 0x0C, 0xFF };
static const u8 uVC[] = { 0x1F, 0x0C, 0xFF };
static const u8 uWC[] = { 0x20, 0x0C, 0xFF };
static const u8 uB1[] = { 0xB, 0x01, 0xFF };
static const u8 uB2[] = { 0xB, 0x02, 0xFF };
static const u8 uB3[] = { 0xB, 0x03, 0xFF };
static const u8 uOW1Prefix[] = { 0x18, 0x20, 0x01, 0xFF };
static const u8 uOW2Prefix[] = { 0x18, 0x20, 0x02, 0xFF };
static const u8 uOW3Prefix[] = { 0x18, 0x20, 0x03, 0xFF };

static const u8* override_course_name(int course)
{
    // Generic override for extra courses, maybe remove this?
    if (course >= LevelConv_PlainLevels_F1)
    {
        static const u8* sBowserFightNames[] = {
            uBowser1Fight
          , uBowser2Fight
          , uBowser3Fight
        };
        return sBowserFightNames[course - LevelConv_PlainLevels_F1];
    }

    if (course < 0)
    {
        static const u8* sOWNames[] = {
            uOW1
          , uOW2
          , uOW3
        };
        return sOWNames[-course - 1];
    }

    // DMG Anihasa village part where you get warped to Andrew
    if (course == LevelConv_PlainLevels_S2)
    {
        return uAndrewSM64;
    }

    return NULL;
}

static const u8* mangle_course_name(int course, int overriden, const u8* name, u8* auxBuffer)
{
    if (LevelConv_PlainLevels_C1 <= course && course <= LevelConv_PlainLevels_C15)
    {
        return name;
    }
    else
    {
        const u8* cutName = !overriden ? custr_advance(name, 3) : name;

        const u8* prefix;
        switch (course)
        {
            case LevelConv_PlainLevels_MC:
                prefix = uMC;
                break;
            case LevelConv_PlainLevels_VC:
                prefix = uVC;
                break;
            case LevelConv_PlainLevels_WC:
                prefix = uWC;
                break;
            case LevelConv_PlainLevels_B1:
                prefix = uB1;
                break;
            case LevelConv_PlainLevels_B2:
                prefix = uB2;
                break;
            case LevelConv_PlainLevels_B3:
                prefix = uB3;
                break;
            case LevelConv_PlainLevels_OW1:
                prefix = uOW1Prefix;
                break;
            case LevelConv_PlainLevels_OW2:
                prefix = uOW2Prefix;
                break;
            case LevelConv_PlainLevels_OW3:
                prefix = uOW3Prefix;
                break;
            default:
                prefix = NULL;
                break;
        }

        if (prefix)
        {
            u8* writer = auxBuffer;

            *writer++ = USTR_DASH;
            writer = ustr_append(writer, prefix);
            *writer++ = USTR_DASH;
            *writer++ = USTR_SPACE;

            writer = ustr_append(writer, cutName);

            return auxBuffer;
        }
        else
        {
            return cutName;
        }
    }
}

static int override_warp_node_target(int sm64lvl)
{
    return 0;
}

static int override_warp_area_target(int sm64lvl)
{
    // DMG C9 has starting area in area 3
    if (sm64lvl == LevelConv_SM64Levels_C9)
    {
        return 3;
    }

    return 0;
}
