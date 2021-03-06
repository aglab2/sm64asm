#include <sm64.h>

class Control : MObject
{
    void Init();
    void Step();
    
    static void sInit() { reinterpret_cast<Control*>(M64_CURR_OBJ_PTR)->Init(); }
    static void sStep() { reinterpret_cast<Control*>(M64_CURR_OBJ_PTR)->Step(); }

public:
    static int Behavior[];
};
