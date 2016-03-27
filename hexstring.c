/*!
 * \file
 * Hex string/binary converter
 */
/*
 * zlib License
 *
 * Copyright (C) 2016 KOBAYASHI Daisuke
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include "hexstring.h"

char* bintohexstr(char* dst, const void* src, size_t n)
{
    if ((dst == 0) || (src == 0) || (n == 0)) {
        return dst;
    }
    static const char hex[] = {
        '0', '1', '2', '3', '4', '5', '6', '7',
        '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
    };
    char* d = dst;
    const unsigned char* s = src;
    while (n--) {
        *d++ = hex[*s >> 4];
        *d++ = hex[*s & 0x0FU];
        s++;
    }
    *d = 0;
    return dst;
}

static unsigned char tobin(char c)
{
    if (c < 0x30) {
        return 0;
    }
    else if (0x30 <= c && c <= 0x39) {
        return c - 0x30;
    }
    else if (0x41 <= c && c <= 0x46) {
        return c - 0x41 + 10;
    }
    else if (0x61 <= c && c <= 0x66) {
        return c - 0x61 + 10;
    }
    else {
        return 0;
    }
}

void* hexstrtobin(void* dst, const char* src)
{
    if ((dst == 0) || (src == 0)) {
        return dst;
    }
    unsigned char* d = dst;
    while (*src) {
        *d = tobin(*src++) << 4;
        *d += tobin(*src++);
        ++d;
    }
    return dst;
}
