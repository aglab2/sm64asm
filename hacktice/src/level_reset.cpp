#include "level_reset.h"
extern "C"
{
    #include "types.h"
    #include "game/game.h"
}
#include "cfg.h"

void LevelReset::onNormal()
{
    if (gControllers->buttonPressed & L_TRIG)
    {
        auto lAction = Config::lAction();
        if (Config::LAction::LEVEL == lAction)
        {
            // reset
            *(char*) (0x8033B21E) = 0x8;
            *(short*)(0x8033B262) = 0x0;
            *(short*)(0x8033B218) = 0x0;
            *(char*) (0x8033B248) = 0x2;
            *(short*)(0x80361414) = 0x5;

            // some other crap
            *(short*)(0x8033B26C) = 0x00;
        }

        if (Config::LAction::ACT == lAction)
        {
            *(short*)(0x8033B24A) = 0x010a;
            *(char*)(0x8033B21E)  = 0x08;
            *(short*)(0x8033B238) = 0x0004;
            *(char*)(0x8033B248) = 0x02;
            *(short*)(0x8033B26C) = 0;
        }
    }
}
