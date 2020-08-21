#include "bank_fixer.h"

void BankFixer::Init()
{
    DmaCopy(0x80409000, 0x1209000, 0x120A000);
    active = 0;
}

int BankFixer::Behavior[] = {
    0x0c000000, (int) sInit,
    0x08000000,
    0x09000000
};