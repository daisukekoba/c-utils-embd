/*
 * zlib License
 *
 * Copyright (C) 2029 KOBAYASHI Daisuke
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
#include "clamp.h"
}

TEST(Clamp, Lower)
{
    EXPECT_EQ(-10, clamp(-20, -10, 10));
    EXPECT_EQ(0, clamp(-10, 0, 10));
    EXPECT_EQ(200, clamp(100, 200, 300));
}

TEST(Clamp, Value)
{
    EXPECT_EQ(-300, clamp(-300, -500, 100));
    EXPECT_EQ(0, clamp(0, 0, 10));
    EXPECT_EQ(1, clamp(1, 0, 10));
    EXPECT_EQ(5, clamp(5, 0, 10));
    EXPECT_EQ(10, clamp(10, 0, 10));
    EXPECT_EQ(50, clamp(50, 0, 500));
    EXPECT_EQ(1001, clamp(1001, 1000, 10000));
}
TEST(Clamp, Upper)
{
    EXPECT_EQ(-20, clamp(10, -300, -20));
    EXPECT_EQ(10, clamp(11, 0, 10));
    EXPECT_EQ(1000, clamp(2000, 0, 1000));
}
