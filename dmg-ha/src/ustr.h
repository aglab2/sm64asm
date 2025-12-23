#pragma once

#include <types.h>

static inline u8* ustr_append(u8* dest, const u8* src)
{
    while (*src != 0xff)
    {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = 0xff;
    return dest;
}

static inline u8* ustr_advance(u8* str, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (*str == 0xff) break;
        str++;
    }
    return str;
}

static inline const u8* custr_advance(const u8* str, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (*str == 0xff) break;
        str++;
    }
    return str;
}
