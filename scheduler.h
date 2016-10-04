/*!
 * \file
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

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <stdbool.h>
#include <stdint.h>

#ifndef SCHEDULER_JOB_NUM
#define SCHEDULER_JOB_NUM (16)
#endif

void Scheduler_Init(void);
void Scheduler_Start(uint32_t tick);
void Scheduler_Stop(void);
bool Scheduler_Register(uint32_t start, uint32_t interval, void (*job)(void));
bool Scheduler_Unregister(void (*job)(void));
void Scheduler_Run(uint32_t tick);

#endif /* SCHEDULER_H_ */
