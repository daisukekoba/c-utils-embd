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

#ifdef __unix
#define stack_t stack_t_
#include <signal.h>
#undef stack_t
#endif

#include <gtest/gtest.h>

extern "C" {
#define STACK_SIZE (8)
#define STACK_ELEMENT_T unsigned char
#include "stack.h"
}

TEST(Stack, Init)
{
    stack_t s;

    stack_Init(&s);
    EXPECT_TRUE(stack_IsEmpty(&s));
    EXPECT_FALSE(stack_IsFull(&s));
}

TEST(Stack, One)
{
    stack_t s;
    unsigned char c = 0;

    stack_Init(&s);
    EXPECT_TRUE(stack_Push(&s, &c));
    EXPECT_FALSE(stack_IsEmpty(&s));
    EXPECT_FALSE(stack_IsFull(&s));

    EXPECT_TRUE(stack_Pop(&s, &c));
    EXPECT_TRUE(stack_IsEmpty(&s));
    EXPECT_FALSE(stack_IsFull(&s));
}

TEST(Stack, EmptyToFull)
{
    stack_t s;
    unsigned char c = 0;

    stack_Init(&s);
    for (int i = 0; i < STACK_SIZE - 1; ++i) {
        SCOPED_TRACE(i);
        EXPECT_TRUE(stack_Push(&s, &c));
    }
    EXPECT_FALSE(stack_IsEmpty(&s));
    EXPECT_FALSE(stack_IsFull(&s));

    EXPECT_TRUE(stack_Push(&s, &c));
    EXPECT_FALSE(stack_IsEmpty(&s));
    EXPECT_TRUE(stack_IsFull(&s));

    EXPECT_FALSE(stack_Push(&s, &c));
    EXPECT_FALSE(stack_IsEmpty(&s));
    EXPECT_TRUE(stack_IsFull(&s));
}

TEST(Stack, FullToEmpty)
{
    stack_t s;
    unsigned char c = 0;

    stack_Init(&s);
    for (int i = 0; i < STACK_SIZE; ++i) {
        stack_Push(&s, &c);
    }
    EXPECT_FALSE(stack_IsEmpty(&s));
    EXPECT_TRUE(stack_IsFull(&s));

    EXPECT_TRUE(stack_Pop(&s, &c));
    EXPECT_FALSE(stack_IsEmpty(&s));
    EXPECT_FALSE(stack_IsFull(&s));
    for (int i = 0; i < STACK_SIZE - 2; ++i) {
        SCOPED_TRACE(i);
        EXPECT_TRUE(stack_Pop(&s, &c));
    }
    EXPECT_FALSE(stack_IsEmpty(&s));
    EXPECT_FALSE(stack_IsFull(&s));

    EXPECT_TRUE(stack_Pop(&s, &c));
    EXPECT_TRUE(stack_IsEmpty(&s));
    EXPECT_FALSE(stack_IsFull(&s));

    EXPECT_FALSE(stack_Pop(&s, &c));
    EXPECT_TRUE(stack_IsEmpty(&s));
    EXPECT_FALSE(stack_IsFull(&s));
}

TEST(RingBuffer, FiLo)
{
    stack_t s;
    unsigned char a;
    unsigned char b;

    stack_Init(&s);
    a = 1;
    stack_Push(&s, &a);
    stack_Pop(&s, &b);
    EXPECT_EQ(1, b);

    a = 2;
    stack_Push(&s, &a);
    a = 3;
    stack_Push(&s, &a);
    stack_Pop(&s, &b);
    EXPECT_EQ(3, b);
    a = 4;
    stack_Push(&s, &a);
    stack_Pop(&s, &b);
    EXPECT_EQ(4, b);
    stack_Pop(&s, &b);
    EXPECT_EQ(2, b);

    for (a = 0; a < STACK_SIZE; ++a) {
        stack_Push(&s, &a);
    }
    for (a = 0; a < STACK_SIZE; ++a) {
        SCOPED_TRACE((int)a);
        stack_Pop(&s, &b);
        EXPECT_EQ(STACK_SIZE - 1 - a, b);
    }
}

TEST(Stack, Top)
{
    stack_t s;
    unsigned char a;
    unsigned char b;

    stack_Init(&s);
    EXPECT_FALSE(stack_Top(&s, &b));
    a = 1;
    stack_Push(&s, &a);
    EXPECT_TRUE(stack_Top(&s, &b));
    EXPECT_EQ(1, b);
    EXPECT_FALSE(stack_IsEmpty(&s));
    EXPECT_TRUE(stack_Top(&s, &b));
    EXPECT_EQ(1, b);
    EXPECT_FALSE(stack_IsEmpty(&s));
    a = 2;
    stack_Push(&s, &a);
    EXPECT_TRUE(stack_Top(&s, &b));
    EXPECT_EQ(2, b);
    stack_Pop(&s, &b);
    EXPECT_TRUE(stack_Top(&s, &b));
    EXPECT_EQ(1, b);
    EXPECT_FALSE(stack_IsEmpty(&s));
}

TEST(Stack, Null)
{
    stack_t s;
    unsigned char a;

    stack_Init(&s);
    stack_Init(0);
    EXPECT_FALSE(stack_Push(&s, 0));
    EXPECT_TRUE(stack_Push(&s, &a));
    EXPECT_FALSE(stack_Pop(&s, 0));
    EXPECT_FALSE(stack_Top(&s, 0));
    EXPECT_FALSE(stack_Push(0, &a));
    EXPECT_FALSE(stack_Push(0, 0));
    EXPECT_FALSE(stack_Pop(0, &a));
    EXPECT_FALSE(stack_Top(0, &a));
}
