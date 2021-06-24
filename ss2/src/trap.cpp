#include "trap.h"

__attribute__((noinline))
void trap()
{
    void (*fn)() = (void(*)()) 0x8000000;
    fn();
}
