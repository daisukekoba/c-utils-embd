/*!
 * \file
 * Scheduler
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

#include "scheduler.h"

typedef struct {
    int32_t remain;
    int32_t start;
    int32_t interval;
    void (*job)(void);
} job_t;

static job_t l_job[SCHEDULER_JOB_NUM];
static uint32_t l_tick;
static bool l_active;

void Scheduler_Init(void)
{
    l_tick = 0;
    l_active = false;
    for (int i = 0; i < SCHEDULER_JOB_NUM; ++i) {
        l_job[i].job = 0;
    }
}

void Scheduler_Start(uint32_t tick)
{
    l_tick = tick;
    l_active = true;
    for (int i = 0; i < SCHEDULER_JOB_NUM; ++i) {
        l_job[i].remain = l_job[i].start;
    }
}

void Scheduler_Stop(void) { l_active = false; }

bool Scheduler_Register(uint32_t start, uint32_t interval, void (*job)(void))
{
    if ((start > (uint32_t)INT32_MAX) || (interval > (uint32_t)INT32_MAX)) {
        return false;
    }
    for (int i = 0; i < SCHEDULER_JOB_NUM; ++i) {
        if (l_job[i].job == job) {
            return false;
        }
    }
    for (int i = 0; i < SCHEDULER_JOB_NUM; ++i) {
        if (l_job[i].job) {
            continue;
        }
        l_job[i].start = (int32_t)start;
        l_job[i].interval = (int32_t)interval;
        l_job[i].job = job;
        return true;
    }
    return false;
}

bool Scheduler_Unregister(void (*job)(void))
{
    for (int i = 0; i < SCHEDULER_JOB_NUM; ++i) {
        if (l_job[i].job == job) {
            l_job[i].job = 0;
            return true;
        }
    }
    return false;
}

void Scheduler_Run(uint32_t tick)
{
    if (!l_active) {
        return;
    }
    uint32_t diff = tick - l_tick;
    if (diff > (uint32_t)INT32_MAX) {
        diff = (uint32_t)INT32_MAX;
    }
    l_tick = tick;
    for (int i = 0; i < SCHEDULER_JOB_NUM; ++i) {
        if (!l_job[i].job) {
            continue;
        }
        l_job[i].remain -= (int32_t)diff;
        if (l_job[i].remain <= 0) {
            l_job[i].remain = l_job[i].interval;
            l_job[i].job();
        }
    }
}
