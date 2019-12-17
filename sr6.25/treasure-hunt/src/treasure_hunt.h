#include <sm64.h>

class TreasureHunt : MObject
{
    void Init();
    void Step();

    static void sInit() { reinterpret_cast<TreasureHunt*>(M64_CURR_OBJ_PTR)->Init(); }
    static void sStep() { reinterpret_cast<TreasureHunt*>(M64_CURR_OBJ_PTR)->Step(); }

public:
    static void Draw();
    static int Behavior[];
};