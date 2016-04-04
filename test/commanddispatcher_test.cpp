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
bool l_proc0;
bool l_proc1;
bool l_proc2;

void reset()
{
    l_proc0 = false;
    l_proc1 = false;
    l_proc2 = false;
}

void proc0(const void* p) { l_proc0 = true; }
void proc1(const void* p) { l_proc1 = true; }
void proc2(const void* p) { l_proc2 = true; }
void proc3(const void* p)
{
    EXPECT_EQ(1, ((uint8_t*)(p))[0]);
    EXPECT_EQ(2, ((uint8_t*)(p))[1]);
}
void proc4(const void* p) {}
void proc5(const void* p) {}
void proc6(const void* p) {}
void proc7(const void* p) {}
void proc8(const void* p) {}
void proc9(const void* p) {}
void proc10(const void* p) {}
void proc11(const void* p) {}
void proc12(const void* p) {}
void proc13(const void* p) {}
void proc14(const void* p) {}
void proc15(const void* p) {}
void proc16(const void* p) {}
}

TEST(CommandDispatcher, Register)
{
    CommandDispatcher_Init();
    EXPECT_TRUE(CommandDispatcher_Register(0, proc0));
    EXPECT_TRUE(CommandDispatcher_Register(1, proc1));
    EXPECT_TRUE(CommandDispatcher_Register(2, proc2));
    EXPECT_TRUE(CommandDispatcher_Register(3, proc3));
    EXPECT_TRUE(CommandDispatcher_Register(4, proc4));
    EXPECT_TRUE(CommandDispatcher_Register(5, proc5));
    EXPECT_TRUE(CommandDispatcher_Register(6, proc6));
    EXPECT_TRUE(CommandDispatcher_Register(7, proc7));
    EXPECT_TRUE(CommandDispatcher_Register(8, proc8));
    EXPECT_TRUE(CommandDispatcher_Register(9, proc9));
    EXPECT_TRUE(CommandDispatcher_Register(10, proc10));
    EXPECT_TRUE(CommandDispatcher_Register(11, proc11));
    EXPECT_TRUE(CommandDispatcher_Register(12, proc12));
    EXPECT_TRUE(CommandDispatcher_Register(13, proc13));
    EXPECT_TRUE(CommandDispatcher_Register(14, proc14));
    EXPECT_TRUE(CommandDispatcher_Register(15, proc15));
    EXPECT_FALSE(CommandDispatcher_Register(16, proc16));
}

TEST(CommandDispatcher, RegisterNull)
{
    CommandDispatcher_Init();
    EXPECT_FALSE(CommandDispatcher_Register(0, 0));
}

TEST(CommandDispatcher, Unregister)
{
    CommandDispatcher_Init();
    EXPECT_TRUE(CommandDispatcher_Register(0, proc0));
    EXPECT_TRUE(CommandDispatcher_Unregister(proc0));

    EXPECT_TRUE(CommandDispatcher_Register(1, proc0));
    EXPECT_FALSE(CommandDispatcher_Unregister(proc1));
    EXPECT_TRUE(CommandDispatcher_Unregister(proc0));
}

TEST(CommandDispatcher, UnregisterNull)
{
    CommandDispatcher_Init();
    EXPECT_TRUE(CommandDispatcher_Register(0, proc0));
    EXPECT_FALSE(CommandDispatcher_Unregister(0));
}

TEST(CommandDispatcher, RegisterSameProc)
{
    CommandDispatcher_Init();
    EXPECT_TRUE(CommandDispatcher_Register(0, proc0));
    EXPECT_FALSE(CommandDispatcher_Register(1, proc0));

    EXPECT_TRUE(CommandDispatcher_Register(2, proc1));
    EXPECT_TRUE(CommandDispatcher_Unregister(proc0));
    EXPECT_FALSE(CommandDispatcher_Register(3, proc1));
}

TEST(CommandDispatcher, Dispatch)
{
    reset();
    uint8_t arg0[] = { 1, 2 };
    CommandDispatcher_Init();
    EXPECT_TRUE(CommandDispatcher_Register(0, proc0));
    EXPECT_TRUE(CommandDispatcher_Register(1, proc1));
    EXPECT_TRUE(CommandDispatcher_Register(1, proc2));
    EXPECT_TRUE(CommandDispatcher_Register(2, proc3));

    CommandDispatcher_Dispatch(0, arg0);
    EXPECT_TRUE(l_proc0);
    EXPECT_FALSE(l_proc1);
    EXPECT_FALSE(l_proc2);

    reset();
    CommandDispatcher_Dispatch(1, arg0);
    EXPECT_FALSE(l_proc0);
    EXPECT_TRUE(l_proc1);
    EXPECT_TRUE(l_proc2);

    reset();
    CommandDispatcher_Dispatch(2, arg0);
    EXPECT_FALSE(l_proc0);
    EXPECT_FALSE(l_proc1);
    EXPECT_FALSE(l_proc2);
}
