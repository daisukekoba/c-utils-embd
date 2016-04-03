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
#include "scheduler.h"
}

namespace {
bool l_job0;
bool l_job1;
bool l_job2;

void reset()
{
    l_job0 = false;
    l_job1 = false;
    l_job2 = false;
}

void job0() { l_job0 = true; }
void job1() { l_job1 = true; }
void job2() { l_job2 = true; }
void job3() {}
void job4() {}
void job5() {}
void job6() {}
void job7() {}
void job8() {}
void job9() {}
void job10() {}
void job11() {}
void job12() {}
void job13() {}
void job14() {}
void job15() {}
void job16() {}
}

TEST(Scheduler, Register)
{
    Scheduler_Init();
    EXPECT_TRUE(Scheduler_Register(0, 1, job0));
    EXPECT_TRUE(Scheduler_Register(0, 1, job1));
    EXPECT_TRUE(Scheduler_Register(0, 1, job2));
    EXPECT_TRUE(Scheduler_Register(0, 1, job3));
    EXPECT_TRUE(Scheduler_Register(0, 1, job4));
    EXPECT_TRUE(Scheduler_Register(0, 1, job5));
    EXPECT_TRUE(Scheduler_Register(0, 1, job6));
    EXPECT_TRUE(Scheduler_Register(0, 1, job7));
    EXPECT_TRUE(Scheduler_Register(0, 1, job8));
    EXPECT_TRUE(Scheduler_Register(0, 1, job9));
    EXPECT_TRUE(Scheduler_Register(0, 1, job10));
    EXPECT_TRUE(Scheduler_Register(0, 1, job11));
    EXPECT_TRUE(Scheduler_Register(0, 1, job12));
    EXPECT_TRUE(Scheduler_Register(0, 1, job13));
    EXPECT_TRUE(Scheduler_Register(0, 1, job14));
    EXPECT_TRUE(Scheduler_Register(0, 1, job15));
    EXPECT_FALSE(Scheduler_Register(0, 1, job16));
}

TEST(Scheduler, RegisterSameJob)
{
    Scheduler_Init();
    EXPECT_TRUE(Scheduler_Register(0, 1, job0));
    EXPECT_FALSE(Scheduler_Register(0, 1, job0));

    EXPECT_TRUE(Scheduler_Register(0, 1, job1));
    EXPECT_TRUE(Scheduler_Unregister(job0));
    EXPECT_FALSE(Scheduler_Register(0, 1, job1));
}

TEST(Scheduler, RegisterLimit)
{
    Scheduler_Init();
    EXPECT_TRUE(Scheduler_Register(0x7FFFFFFF, 0x7FFFFFFF, job0));
    EXPECT_FALSE(Scheduler_Register(0x80000000, 0x7FFFFFFF, job1));
    EXPECT_FALSE(Scheduler_Register(0x7FFFFFFF, 0x80000000, job2));
}

TEST(Scheduler, Unregister)
{
    Scheduler_Init();
    EXPECT_TRUE(Scheduler_Register(0, 1, job0));
    EXPECT_TRUE(Scheduler_Unregister(job0));

    EXPECT_TRUE(Scheduler_Register(0, 1, job0));
    EXPECT_FALSE(Scheduler_Unregister(job1));
}

TEST(Scheduler, StopAndStart)
{
    reset();
    Scheduler_Init();
    EXPECT_TRUE(Scheduler_Register(0, 2, job0));
    for (int i = 100; i < 200; ++i) {
        Scheduler_Run(i);
    }
    EXPECT_FALSE(l_job0);

    Scheduler_Start(200);
    Scheduler_Run(200);
    EXPECT_TRUE(l_job0);
    reset();
    Scheduler_Run(201);
    EXPECT_FALSE(l_job0);
    Scheduler_Run(202);
    EXPECT_TRUE(l_job0);
    reset();

    Scheduler_Stop();
    EXPECT_FALSE(l_job0);
    for (int i = 203; i < 300; ++i) {
        Scheduler_Run(i);
    }
    EXPECT_FALSE(l_job0);
}

TEST(Scheduler, Overflow)
{
    reset();
    Scheduler_Init();
    EXPECT_TRUE(Scheduler_Register(0, 4, job0));
    Scheduler_Start(0xFFFFFFFE);
    Scheduler_Run(0xFFFFFFFE);
    EXPECT_TRUE(l_job0);
    reset();
    Scheduler_Run(0);
    EXPECT_FALSE(l_job0);
    Scheduler_Run(2);
    EXPECT_TRUE(l_job0);
}

TEST(Scheduler, StartTime)
{
    reset();
    Scheduler_Init();
    EXPECT_TRUE(Scheduler_Register(1, 2, job0));
    EXPECT_TRUE(Scheduler_Register(0, 3, job1));

    Scheduler_Start(1000);
    Scheduler_Run(1000);
    EXPECT_FALSE(l_job0);
    EXPECT_TRUE(l_job1);
    reset();
    Scheduler_Run(1001);
    EXPECT_TRUE(l_job0);
    EXPECT_FALSE(l_job1);
    reset();
    Scheduler_Run(1002);
    EXPECT_FALSE(l_job0);
    EXPECT_FALSE(l_job1);
    reset();
    Scheduler_Run(1003);
    EXPECT_TRUE(l_job0);
    EXPECT_TRUE(l_job1);
    reset();
}

TEST(Scheduler, RegularIntervals)
{
    reset();
    Scheduler_Init();
    EXPECT_TRUE(Scheduler_Register(0, 2, job0));
    EXPECT_TRUE(Scheduler_Register(0, 3, job1));
    EXPECT_TRUE(Scheduler_Register(0, 5, job2));

    Scheduler_Start(1000);
    Scheduler_Run(1000);
    EXPECT_TRUE(l_job0);
    EXPECT_TRUE(l_job1);
    EXPECT_TRUE(l_job2);
    reset();

    Scheduler_Run(1001);
    EXPECT_FALSE(l_job0);
    EXPECT_FALSE(l_job1);
    EXPECT_FALSE(l_job2);

    Scheduler_Run(1002);
    EXPECT_TRUE(l_job0);
    EXPECT_FALSE(l_job1);
    EXPECT_FALSE(l_job2);
    reset();

    Scheduler_Run(1003);
    EXPECT_FALSE(l_job0);
    EXPECT_TRUE(l_job1);
    EXPECT_FALSE(l_job2);
    reset();

    Scheduler_Run(1004);
    EXPECT_TRUE(l_job0);
    EXPECT_FALSE(l_job1);
    EXPECT_FALSE(l_job2);
    reset();

    Scheduler_Run(1005);
    EXPECT_FALSE(l_job0);
    EXPECT_FALSE(l_job1);
    EXPECT_TRUE(l_job2);
}

TEST(Scheduler, IrregularIntervals)
{
    reset();
    Scheduler_Init();
    EXPECT_TRUE(Scheduler_Register(0, 2, job0));
    EXPECT_TRUE(Scheduler_Register(0, 3, job1));
    EXPECT_TRUE(Scheduler_Register(0, 5, job2));

    Scheduler_Start(1000);
    Scheduler_Run(1000);
    reset();

    Scheduler_Run(1005);
    EXPECT_TRUE(l_job0);
    EXPECT_TRUE(l_job1);
    EXPECT_TRUE(l_job2);
    reset();

    Scheduler_Run(1006);
    EXPECT_FALSE(l_job0);
    EXPECT_FALSE(l_job1);
    EXPECT_FALSE(l_job2);

    Scheduler_Run(1008);
    EXPECT_TRUE(l_job0);
    EXPECT_TRUE(l_job1);
    EXPECT_FALSE(l_job2);
    reset();

    Scheduler_Run(1010);
    EXPECT_TRUE(l_job0);
    EXPECT_FALSE(l_job1);
    EXPECT_TRUE(l_job2);
}

TEST(Scheduler, LongIntervals)
{
    reset();
    Scheduler_Init();
    EXPECT_TRUE(Scheduler_Register(0, 2, job0));
    EXPECT_TRUE(Scheduler_Register(0, 0x7FFFFFFF, job1));

    Scheduler_Start(0);
    Scheduler_Run(0);
    reset();

    Scheduler_Run(INT32_MAX);
    EXPECT_TRUE(l_job0);
    EXPECT_TRUE(l_job1);
    reset();

    Scheduler_Run(0);
    EXPECT_TRUE(l_job0);
    EXPECT_TRUE(l_job1);
    reset();

    Scheduler_Run(UINT32_MAX);
    EXPECT_TRUE(l_job0);
    EXPECT_TRUE(l_job1);
}
