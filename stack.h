/*!
 * \file
 * Stack
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

#include <stdbool.h>
#include <stdint.h>

#ifndef STACK_SIZE
#define STACK_SIZE (32)
#endif

#ifndef STACK_ELEMENT_T
#define STACK_ELEMENT_T int
#endif

typedef struct {
    STACK_ELEMENT_T buf[STACK_SIZE];
    uint8_t p;
} stack_t;

/*! Initialize */
static void stack_Init(stack_t* buf)
{
    buf->p = 0;
}

/*! Test whether stack is empty */
static bool stack_IsEmpty(const stack_t* buf)
{
    return buf->p == 0;
}

/*! Test whether stack is full */
static bool stack_IsFull(const stack_t* buf)
{
    return buf->p == STACK_SIZE;
}

/*! Insert element at the top */
static bool stack_Push(stack_t* buf, const STACK_ELEMENT_T* e)
{
    if (stack_IsFull(buf)) {
        return /*Full*/ false;
    }

    buf->buf[buf->p] = *e;
    ++buf->p;
    return true;
}

/*! Take the top element */
static bool stack_Pop(stack_t* buf, STACK_ELEMENT_T* e)
{
    if (stack_IsEmpty(buf)) {
        return /*Empty*/ false;
    }

    --buf->p;
    *e = buf->buf[buf->p];
    return true;
}

/*! Access the top element */
static bool stack_Top(const stack_t* buf, STACK_ELEMENT_T* e)
{
    if (stack_IsEmpty(buf)) {
        return /*Empty*/ false;
    }

    *e = buf->buf[buf->p - 1];
    return true;
}
