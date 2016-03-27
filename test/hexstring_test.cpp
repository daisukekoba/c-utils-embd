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

#include <cstring>
#include <gtest/gtest.h>

extern "C" {
#include "hexstring.h"
}

TEST(HexString, ToHexString)
{
    const unsigned char src[] = {
        1, 2, 3, 4, 252, 253, 254, 255
    };
    char dst[17];
    EXPECT_EQ(dst, bintohexstr(dst, src, 8));
    EXPECT_EQ(16u, strlen(dst));
    EXPECT_STREQ("01020304FCFDFEFF", dst);

    const unsigned char c = 0;
    bintohexstr(dst, &c, 1);
    EXPECT_EQ(2u, strlen(dst));
    EXPECT_STREQ("00", dst);
}

TEST(HexString, ToHexStringNull)
{
    const unsigned char src[] = {
        1
    };
    char dst[2] = {};

    EXPECT_EQ(0, bintohexstr(0, src, 1));

    EXPECT_EQ(dst, bintohexstr(dst, 0, 1));
    EXPECT_STREQ("", dst);

    EXPECT_EQ(dst, bintohexstr(dst, src, 0));
    EXPECT_STREQ("", dst);
}

TEST(HexString, ToBin)
{
    const char* src = "12345678";
    char dst[4];
    EXPECT_EQ(dst, hexstrtobin(dst, src));
    EXPECT_EQ(0x12, dst[0]);
    EXPECT_EQ(0x34, dst[1]);
    EXPECT_EQ(0x56, dst[2]);
    EXPECT_EQ(0x78, dst[3]);
}

TEST(HexString, ToBinNull)
{
    const char* src = "A";
    char dst[2] = {};
    EXPECT_EQ(0, hexstrtobin(0, src));

    EXPECT_EQ(dst, hexstrtobin(dst, 0));
    EXPECT_STREQ("", dst);
}
