static const u8 sLevelWarpLevels[] = {
    LevelConv_PlainLevels_C1,
    LevelConv_PlainLevels_C2,
    LevelConv_PlainLevels_C3,
    LevelConv_PlainLevels_C4,
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
    LevelConv_PlainLevels_C15,

    LevelConv_PlainLevels_B1,
    LevelConv_PlainLevels_B2,
    // LevelConv_PlainLevels_B3,

    LevelConv_PlainLevels_Slide,

    LevelConv_PlainLevels_MC,
    LevelConv_PlainLevels_WC,
    LevelConv_PlainLevels_VC,

    LevelConv_PlainLevels_S1,
    LevelConv_PlainLevels_S2,
    // LevelConv_PlainLevels_S3,

    // extras, currently 3 courses
    LevelConv_PlainLevels_F1,
    LevelConv_PlainLevels_F2,
    // LevelConv_PlainLevels_F3,
};

#define kSelectedWarpLimit (sizeof(sLevelWarpLevels) / sizeof(sLevelWarpLevels[0]))
#define kLevelWarpExtraStart (kSelectedWarpLimit - kExtraCoursesCount)

// Game does not store names for each extra course (fights currently), so we define them here.
static const u8 uAndrewSM64[] = { 0x0A, 0x17, 0x0D, 0x1B, 0x0E, 0x20, 0x1C, 0x16, 0x06, 0x04, 0xFF };
static const u8 uBowser1Fight[] = { 0X0B, 0x18, 0x20, 0x1C, 0x0E, 0x1B, 0x9E, 0x01, 0x9E, 0x0F, 0x12, 0x10, 0x11, 0x1D, 0xFF };
static const u8 uBowser2Fight[] = { 0X0B, 0x18, 0x20, 0x1C, 0x0E, 0x1B, 0x9E, 0x02, 0x9E, 0x0F, 0x12, 0x10, 0x11, 0x1D, 0xFF };
static const u8 uBowser3Fight[] = { 0X0B, 0x18, 0x20, 0x1C, 0x0E, 0x1B, 0x9E, 0x03, 0x9E, 0x0F, 0x12, 0x10, 0x11, 0x1D, 0xFF };
static const u8 uEnding[] = { 0x0E, 0x17, 0x0D, 0x12, 0x17, 0x10, 0xFF };

static const u8* override_course_name(int course)
{
    if (course >= 25)
    {
        static const u8* uExtraCoursesNames[] = { uBowser1Fight, uBowser2Fight, uBowser3Fight };
        return uExtraCoursesNames[course - 25];
    }

    if (course == LevelConv_PlainLevels_S2)
    {
        return uAndrewSM64;
    }

    return NULL;
}
