#include "control.h"
#include "path_part.h"
#include "bank_fixer.h"

#define REGISTER_BEHAVIOR(list, obj) list, 0x04000000, (int) obj::Behavior,

int _start[] =
{
    REGISTER_BEHAVIOR(0x00040000, Control)   // 409000
    REGISTER_BEHAVIOR(0x00040000, Part)      // 40900C
    REGISTER_BEHAVIOR(0x00040000, BankFixer) // 409018
};