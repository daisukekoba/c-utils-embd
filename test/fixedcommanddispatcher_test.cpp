/*
 * zlib License
 *
 * Copyright (C) 2018 KOBAYASHI Daisuke
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
#include "fixedcommanddispatcher.h"
}

namespace {
bool l_func0;
bool l_func1;
bool l_func2;

void reset()
{
    l_func0 = false;
    l_func1 = false;
    l_func2 = false;
}

void func0(const void* p) { l_func0 = true; }
void func1(const void* p) { l_func1 = true; }
void func2(const void* p) { l_func2 = true; }
} // unnamed namespace

const func_t func[] = {
    { 0, func0 },
    { 1, func1 },
    { 2, func2 },
};

const int func_num = sizeof(func)/sizeof(func[0]);

TEST(FixedCommandDispatcher, Dispatch)
{
    reset();
    uint8_t arg0[] = { 1, 2 };

    FixedCommandDispatcher_Dispatch(0, arg0);
    EXPECT_TRUE(l_func0);
    EXPECT_FALSE(l_func1);
    EXPECT_FALSE(l_func2);

    reset();
    FixedCommandDispatcher_Dispatch(1, arg0);
    EXPECT_FALSE(l_func0);
    EXPECT_TRUE(l_func1);
    EXPECT_FALSE(l_func2);

    reset();
    FixedCommandDispatcher_Dispatch(2, arg0);
    EXPECT_FALSE(l_func0);
    EXPECT_FALSE(l_func1);
    EXPECT_TRUE(l_func2);
}

