/*!
 * \file
 */
/*
 * zlib License
 *
 * Copyright (C) 2020 KOBAYASHI Daisuke
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

#ifndef CLAMP_H_
#define CLAMP_H_

#ifndef CLAMP_T
#define CLAMP_T int
#endif

#define CLAMP_MIN(a, b) (((a) < (b)) ? (a) : (b))
#define CLAMP_MAX(a, b) (((a) > (b)) ? (a) : (b))

/** Clamps a variable to a given range.
 *
 * @param value value to clamp
 * @param min lower limit
 * @param max upper limit
 */
static inline CLAMP_T clamp(CLAMP_T value, CLAMP_T min, CLAMP_T max)
{
    return CLAMP_MIN(CLAMP_MAX(value, min), max);
}

#undef CLAMP_MIN
#undef CLAMP_MAX

#endif /* CLAMP_H_ */
