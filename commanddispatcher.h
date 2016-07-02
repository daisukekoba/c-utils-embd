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

#ifndef COMMANDDISPATCHER_H_
#define COMMANDDISPATCHER_H_

#include <stdbool.h>
#include <stdint.h>

#define COMMANDDISPATCHER_PROC_NUM (16)

void CommandDispatcher_Init(void);
bool CommandDispatcher_Register(uint8_t id, void (*proc)(const void*));
bool CommandDispatcher_Unregister(void (*proc)(const void*));
void CommandDispatcher_Dispatch(uint8_t id, const void* p);

#endif /* COMMANDDISPATCHER_H_ */
