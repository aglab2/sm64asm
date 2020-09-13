#include "cfg.h"
extern "C"
{
    #include "types.h"
    #include "game/game.h"
    #include "game/print.h"
}
#include "array_size.h"

static char sStickStyle = 0;
static char sShowButtons = 0;
static char sLAction = 0;

struct ConfigDescriptor
{
    char& value;
    const char* name;
    const char** valueNames;
    char maxValueCount;
};

static const char* inputValueNames[] = { "OFF", "TE*T", "GRAPHICS" };
static const char* onOffValueNames[] = { "OFF", "ON" };
static const char* lActioNames[]     = { "OFF", "NORMAL", "ACT", "STATE" };

#define VALUE_NAMES(x) x, ARRAY_SIZE(x)
static ConfigDescriptor sDescriptors[] = 
{
    { sShowButtons, "BUTTONS",  VALUE_NAMES(onOffValueNames) },
    { sStickStyle,  "STICK",    VALUE_NAMES(inputValueNames) },
    { sLAction,     "L RESET",  VALUE_NAMES(lActioNames) },
};

constexpr int sMaxAllowedOption = sizeof(sDescriptors) / sizeof(*sDescriptors) - 1;
static int sPickedOption = sMaxAllowedOption / 2;

void renderOptionAt(ConfigDescriptor& desc, int x, int y)
{
    auto value = desc.value;
    print_text_centered(x, y,      desc.name);
    print_text_centered(x, y - 20, desc.valueNames[(int) value]);
}

void render()
{
    constexpr int height = 190;
    if (0 != sPickedOption)
    {
        renderOptionAt(sDescriptors[sPickedOption - 1], 80, height);
    }

    renderOptionAt(sDescriptors[sPickedOption], 160, height);

    if (sPickedOption != sMaxAllowedOption)
    {
        renderOptionAt(sDescriptors[sPickedOption + 1], 80 + 160, height);
    }
}

void processInputs()
{
    auto& desc = sDescriptors[sPickedOption];
    if (gControllers->buttonPressed & L_JPAD)
    {
        if (sPickedOption != 0)
        {
            sPickedOption--;
            return;
        }
    }
    if (gControllers->buttonPressed & R_JPAD)
    {
        if (sPickedOption != sMaxAllowedOption)
        {
            sPickedOption++;
            return;
        }
    }
    if (gControllers->buttonPressed & U_JPAD)
    {
        if (desc.value != desc.maxValueCount - 1)
        {
            desc.value++;
            return;
        }
    }
    if (gControllers->buttonPressed & D_JPAD)
    {
        if (desc.value != 0)
        {
            desc.value--;
            return;
        }
    }
}

void Config::onPause()
{
    render();
    processInputs();
}

Config::StickStyle Config::showStick()
{
    return (Config::StickStyle) sStickStyle;
}

bool Config::showButtons()
{
    return sShowButtons;
}

Config::LAction Config::lAction()
{
    return (Config::LAction) sLAction;
}