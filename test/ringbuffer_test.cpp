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
#define RINGBUFFER_SIZE (15)
#define RINGBUFFER_ELEMENT_T char
#include "ringbuffer.h"
}

TEST(RingBuffer,Init)
{
    ringbuffer_t rb;

    ringbuffer_Init(&rb);
    EXPECT_TRUE(ringbuffer_IsEmpty(&rb));
    EXPECT_FALSE(ringbuffer_IsFull(&rb));
}

TEST(RingBuffer,One)
{
    ringbuffer_t rb;
    char c = 0;

    ringbuffer_Init(&rb);
    EXPECT_TRUE(ringbuffer_Push(&rb, &c));
    EXPECT_FALSE(ringbuffer_IsEmpty(&rb));
    EXPECT_FALSE(ringbuffer_IsFull(&rb));

    EXPECT_TRUE(ringbuffer_Pop(&rb, &c));
    EXPECT_TRUE(ringbuffer_IsEmpty(&rb));
    EXPECT_FALSE(ringbuffer_IsFull(&rb));
}

TEST(RingBuffer,EmptyToFull)
{
    ringbuffer_t rb;
    char c = 0;

    ringbuffer_Init(&rb);
    for (int i = 0; i < RINGBUFFER_SIZE - 1; ++i) {
        SCOPED_TRACE(i);
        EXPECT_TRUE(ringbuffer_Push(&rb, &c));
    }
    EXPECT_FALSE(ringbuffer_IsEmpty(&rb));
    EXPECT_FALSE(ringbuffer_IsFull(&rb));

    EXPECT_TRUE(ringbuffer_Push(&rb, &c));
    EXPECT_FALSE(ringbuffer_IsEmpty(&rb));
    EXPECT_TRUE(ringbuffer_IsFull(&rb));

    EXPECT_FALSE(ringbuffer_Push(&rb, &c));
    EXPECT_FALSE(ringbuffer_IsEmpty(&rb));
    EXPECT_TRUE(ringbuffer_IsFull(&rb));
}

TEST(RingBuffer,FullToEmpty)
{
    ringbuffer_t rb;
    char c = 0;

    ringbuffer_Init(&rb);
    for (int i = 0; i < RINGBUFFER_SIZE; ++i) {
        ringbuffer_Push(&rb, &c);
    }
    EXPECT_FALSE(ringbuffer_IsEmpty(&rb));
    EXPECT_TRUE(ringbuffer_IsFull(&rb));

    EXPECT_TRUE(ringbuffer_Pop(&rb, &c));
    EXPECT_FALSE(ringbuffer_IsEmpty(&rb));
    EXPECT_FALSE(ringbuffer_IsFull(&rb));
    for (int i = 0; i < RINGBUFFER_SIZE - 2; ++i) {
        SCOPED_TRACE(i);
        EXPECT_TRUE(ringbuffer_Pop(&rb, &c));
    }
    EXPECT_FALSE(ringbuffer_IsEmpty(&rb));
    EXPECT_FALSE(ringbuffer_IsFull(&rb));

    EXPECT_TRUE(ringbuffer_Pop(&rb, &c));
    EXPECT_TRUE(ringbuffer_IsEmpty(&rb));
    EXPECT_FALSE(ringbuffer_IsFull(&rb));

    EXPECT_FALSE(ringbuffer_Pop(&rb, &c));
    EXPECT_TRUE(ringbuffer_IsEmpty(&rb));
    EXPECT_FALSE(ringbuffer_IsFull(&rb));
}

TEST(RingBuffer,FiFo)
{
    ringbuffer_t rb;
    char a;
    char b;

    ringbuffer_Init(&rb);
    a = 1;
    ringbuffer_Push(&rb, &a);
    ringbuffer_Pop(&rb, &b);
    EXPECT_EQ(1, b);

    a = 2;
    ringbuffer_Push(&rb, &a);
    a = 3;
    ringbuffer_Push(&rb, &a);
    ringbuffer_Pop(&rb, &b);
    EXPECT_EQ(2, b);
    a = 4;
    ringbuffer_Push(&rb, &a);
    ringbuffer_Pop(&rb, &b);
    EXPECT_EQ(3, b);
    ringbuffer_Pop(&rb, &b);
    EXPECT_EQ(4, b);

    for (a = 0; a < RINGBUFFER_SIZE; ++a) {
        ringbuffer_Push(&rb, &a);
    }
    for (a = 0; a < RINGBUFFER_SIZE; ++a) {
        SCOPED_TRACE((int)a);
        ringbuffer_Pop(&rb, &b);
        EXPECT_EQ(a, b);
    }
}
