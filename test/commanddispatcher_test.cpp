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
#include "commanddispatcher.h"
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
void func3(const void* p)
{
    EXPECT_EQ(1, ((uint8_t*)(p))[0]);
    EXPECT_EQ(2, ((uint8_t*)(p))[1]);
}
void func4(const void* p) {}
void func5(const void* p) {}
void func6(const void* p) {}
void func7(const void* p) {}
void func8(const void* p) {}
void func9(const void* p) {}
void func10(const void* p) {}
void func11(const void* p) {}
void func12(const void* p) {}
void func13(const void* p) {}
void func14(const void* p) {}
void func15(const void* p) {}
void func16(const void* p) {}
}

TEST(CommandDispatcher, Register)
{
    CommandDispatcher_Init();
    EXPECT_TRUE(CommandDispatcher_Register(0, func0));
    EXPECT_TRUE(CommandDispatcher_Register(1, func1));
    EXPECT_TRUE(CommandDispatcher_Register(2, func2));
    EXPECT_TRUE(CommandDispatcher_Register(3, func3));
    EXPECT_TRUE(CommandDispatcher_Register(4, func4));
    EXPECT_TRUE(CommandDispatcher_Register(5, func5));
    EXPECT_TRUE(CommandDispatcher_Register(6, func6));
    EXPECT_TRUE(CommandDispatcher_Register(7, func7));
    EXPECT_TRUE(CommandDispatcher_Register(8, func8));
    EXPECT_TRUE(CommandDispatcher_Register(9, func9));
    EXPECT_TRUE(CommandDispatcher_Register(10, func10));
    EXPECT_TRUE(CommandDispatcher_Register(11, func11));
    EXPECT_TRUE(CommandDispatcher_Register(12, func12));
    EXPECT_TRUE(CommandDispatcher_Register(13, func13));
    EXPECT_TRUE(CommandDispatcher_Register(14, func14));
    EXPECT_TRUE(CommandDispatcher_Register(15, func15));
    EXPECT_FALSE(CommandDispatcher_Register(16, func16));
}

TEST(CommandDispatcher, RegisterNull)
{
    CommandDispatcher_Init();
    EXPECT_FALSE(CommandDispatcher_Register(0, 0));
}

TEST(CommandDispatcher, Unregister)
{
    CommandDispatcher_Init();
    EXPECT_TRUE(CommandDispatcher_Register(0, func0));
    EXPECT_TRUE(CommandDispatcher_Unregister(func0));

    EXPECT_TRUE(CommandDispatcher_Register(1, func0));
    EXPECT_FALSE(CommandDispatcher_Unregister(func1));
    EXPECT_TRUE(CommandDispatcher_Unregister(func0));
}

TEST(CommandDispatcher, UnregisterNull)
{
    CommandDispatcher_Init();
    EXPECT_TRUE(CommandDispatcher_Register(0, func0));
    EXPECT_FALSE(CommandDispatcher_Unregister(0));
}

TEST(CommandDispatcher, RegisterSameFunc)
{
    CommandDispatcher_Init();
    EXPECT_TRUE(CommandDispatcher_Register(0, func0));
    EXPECT_FALSE(CommandDispatcher_Register(1, func0));

    EXPECT_TRUE(CommandDispatcher_Register(2, func1));
    EXPECT_TRUE(CommandDispatcher_Unregister(func0));
    EXPECT_FALSE(CommandDispatcher_Register(3, func1));
}

TEST(CommandDispatcher, Dispatch)
{
    reset();
    uint8_t arg0[] = { 1, 2 };
    CommandDispatcher_Init();
    EXPECT_TRUE(CommandDispatcher_Register(0, func0));
    EXPECT_TRUE(CommandDispatcher_Register(1, func1));
    EXPECT_TRUE(CommandDispatcher_Register(1, func2));
    EXPECT_TRUE(CommandDispatcher_Register(2, func3));

    CommandDispatcher_Dispatch(0, arg0);
    EXPECT_TRUE(l_func0);
    EXPECT_FALSE(l_func1);
    EXPECT_FALSE(l_func2);

    reset();
    CommandDispatcher_Dispatch(1, arg0);
    EXPECT_FALSE(l_func0);
    EXPECT_TRUE(l_func1);
    EXPECT_TRUE(l_func2);

    reset();
    CommandDispatcher_Dispatch(2, arg0);
    EXPECT_FALSE(l_func0);
    EXPECT_FALSE(l_func1);
    EXPECT_FALSE(l_func2);
}
