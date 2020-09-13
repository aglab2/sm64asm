#include "input_viewer.h"
extern "C"
{
    #include "types.h"
    #include "game/game.h"
    #include "game/print.h"
    #include "libc/string.h"
}
#include "array_size.h"
#include "cfg.h"

struct ButtonDescriptor
{
    const char* name;
    u16 mask; 
};

static ButtonDescriptor sButtonDescriptors[] = {
    { "A", A_BUTTON },
    { "B", B_BUTTON },
    { "*", Z_TRIG },
    { "C", R_TRIG },
    { "DU", U_JPAD },
    { "DL", L_JPAD },
    { "DR", R_JPAD },
    { "DD", D_JPAD },
    { "U", U_CBUTTONS },
    { "L", L_CBUTTONS },
    { "R", R_CBUTTONS },
    { "D", D_CBUTTONS },
};

void InputViewer::onNormal()
{
    auto stickStyle = Config::showStick();

    auto x = gControllers->stickX;
    auto y = gControllers->stickY;
    
    if (Config::StickStyle::VALUE == stickStyle)
    {
        print_text_fmt_int(20, 40, "* %d", x);
        print_text_fmt_int(20, 20, "Y %d", y);
    }
    if (Config::StickStyle::GRAPHICS == stickStyle)
    {
        print_text(30, 30, "0");

        x = x / 64 * 20;
        y = y / 64 * 20;

        print_text(30 + x, 30 + y, "0");
    }

    auto showButtons = Config::showButtons();
    if (showButtons)
    {
        auto activeButtons = gControllers->buttonPressed | gControllers->buttonDown;
        int off = 0;
        for (int i = 0; i < ARRAY_SIZE(sButtonDescriptors); i++)
        {
            auto& desc = sButtonDescriptors[i];
            if (activeButtons & desc.mask)
            {
                print_text(80 + off, 20, desc.name);
                off += 15 * strlen(desc.name);
            }
        }
    }
}