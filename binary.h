/*!
 * \file
 * Binary literals
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

#ifndef BINARY_H_
#define BINARY_H_

#define BINARY_1(x, y) B##x = y
#define BINARY_2(x, y) BINARY_1(x##0, (y * 2)), BINARY_1(x##1, (y * 2 + 1))
#define BINARY_3(x, y) BINARY_2(x##0, (y * 2)), BINARY_2(x##1, (y * 2 + 1))
#define BINARY_4(x, y) BINARY_3(x##0, (y * 2)), BINARY_3(x##1, (y * 2 + 1))
#define BINARY_5(x, y) BINARY_4(x##0, (y * 2)), BINARY_4(x##1, (y * 2 + 1))
#define BINARY_6(x, y) BINARY_5(x##0, (y * 2)), BINARY_5(x##1, (y * 2 + 1))
#define BINARY_7(x, y) BINARY_6(x##0, (y * 2)), BINARY_6(x##1, (y * 2 + 1))
#define BINARY_8(x, y) BINARY_7(x##0, (y * 2)), BINARY_7(x##1, (y * 2 + 1))
#define BINARY_9(x, y) BINARY_8(x##0, (y * 2)), BINARY_8(x##1, (y * 2 + 1))
#define BINARY_10(x, y) BINARY_9(x##0, (y * 2)), BINARY_9(x##1, (y * 2 + 1))
#define BINARY_11(x, y) BINARY_10(x##0, (y * 2)), BINARY_10(x##1, (y * 2 + 1))
#define BINARY_12(x, y) BINARY_11(x##0, (y * 2)), BINARY_11(x##1, (y * 2 + 1))
#define BINARY_13(x, y) BINARY_12(x##0, (y * 2)), BINARY_12(x##1, (y * 2 + 1))
#define BINARY_14(x, y) BINARY_13(x##0, (y * 2)), BINARY_13(x##1, (y * 2 + 1))
#define BINARY_15(x, y) BINARY_14(x##0, (y * 2)), BINARY_14(x##1, (y * 2 + 1))
#define BINARY_16(x, y) BINARY_15(x##0, (y * 2)), BINARY_15(x##1, (y * 2 + 1))

#define BINARY_ENUM(x) enum { BINARY_##x(0, 0), BINARY_##x(1, 1) }

BINARY_ENUM(8);
BINARY_ENUM(16);

#endif /* BINARY_H_ */
