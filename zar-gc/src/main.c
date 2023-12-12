#include "types.h"

#include "image_select.h"

static void onPause()
{
    imageSelect();
}

uintptr_t _start[] = {
    (uintptr_t) onPause,
};
