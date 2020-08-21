#include <sm64.h>

class BankFixer : MObject
{
    void Init();
    
    static void sInit() { reinterpret_cast<BankFixer*>(M64_CURR_OBJ_PTR)->Init(); }

public:
    static int Behavior[];
};
