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

#include <gtest/gtest.h>

extern "C" {
#include "binary.h"
}

TEST(Binary, Int8)
{
    EXPECT_EQ(0, (int)B00000000);
    EXPECT_EQ(1, B00000001);
    EXPECT_EQ(254, B11111110);
    EXPECT_EQ(255, B11111111);
}

TEST(Binary, Int8Calc)
{
    int a = B00000001 + B00000010;
    EXPECT_EQ(B00000011, a);

    int b = B11111111 - B11000000;
    EXPECT_EQ(B00111111, b);
}

TEST(Binary, Int16)
{
    EXPECT_EQ(0, (int)B0000000000000000);
    EXPECT_EQ(1, B0000000000000001);
    EXPECT_EQ(65534, B1111111111111110);
    EXPECT_EQ(65535, B1111111111111111);
}

TEST(Binary, Int16Calc)
{
    int a = B0011000000000000 + B0000110000000000;
    EXPECT_EQ(B0011110000000000, a);

    int b = B1111111100000000 - B1111110000000000;
    EXPECT_EQ(B0000001100000000, b);
}
