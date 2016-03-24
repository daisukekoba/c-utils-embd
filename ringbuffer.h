/*!
 * \file
 * Ring buffer
 *
 * Fixed size queue
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

#ifndef RINGBUFFER_SIZE
#define RINGBUFFER_SIZE (31)
#endif

#ifndef RINGBUFFER_ELEMENT_T
#define RINGBUFFER_ELEMENT_T int
#endif

typedef struct {
    RINGBUFFER_ELEMENT_T buf[RINGBUFFER_SIZE + 1];
    uint8_t rp;
    uint8_t wp;
} ringbuffer_t;

static uint8_t ringbuffer_next(uint8_t p)
{
    ++p;
    if (p >= RINGBUFFER_SIZE + 1) {
        p = 0;
    }
    return p;
}

static uint8_t ringbuffer_prev(uint8_t p)
{
    if (p == 0) {
        p = RINGBUFFER_SIZE + 1;
    }
    --p;
    return p;
}

static void ringbuffer_Init(ringbuffer_t* buf)
{
    buf->rp = 0;
    buf->wp = 0;
}

static bool ringbuffer_IsEmpty(const ringbuffer_t* buf)
{
    return buf->wp == buf->rp;
}

static bool ringbuffer_IsFull(const ringbuffer_t* buf)
{
    return ringbuffer_next(buf->wp) == buf->rp;
}

static bool ringbuffer_Push(ringbuffer_t* buf, const RINGBUFFER_ELEMENT_T* e)
{
    if (ringbuffer_IsFull(buf)) {
        return /*Full*/ false;
    }

    buf->buf[buf->wp] = *e;
    buf->wp = ringbuffer_next(buf->wp);
    return true;
}

static bool ringbuffer_Pop(ringbuffer_t* buf, RINGBUFFER_ELEMENT_T* e)
{
    if (ringbuffer_IsEmpty(buf)) {
        return /*Empty*/ false;
    }

    *e = buf->buf[buf->rp];
    buf->rp = ringbuffer_next(buf->rp);
    return true;
}

static bool ringbuffer_Front(const ringbuffer_t* buf, RINGBUFFER_ELEMENT_T* e)
{
    if (ringbuffer_IsEmpty(buf)) {
        return /*Empty*/ false;
    }

    *e = buf->buf[buf->rp];
    return true;
}

static bool ringbuffer_Back(const ringbuffer_t* buf, RINGBUFFER_ELEMENT_T* e)
{
    if (ringbuffer_IsEmpty(buf)) {
        return /*Empty*/ false;
    }

    *e = buf->buf[ringbuffer_prev(buf->wp)];
    return true;
}
