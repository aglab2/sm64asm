#pragma once

namespace Config
{
    void onPause();

    enum class StickStyle
    {
        OFF,
        VALUE,
        GRAPHICS,  
    };
    StickStyle showStick();

    bool showButtons();

    enum class LAction
    {
        OFF,
        LEVEL,
        ACT,
        STATE,
    };
    LAction lAction();
};
