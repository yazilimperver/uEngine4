/**
 * @file   pixel_type.h
 * @date   5/22/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_PIXEL_TYPE_H
#define INC_PIXEL_TYPE_H

#include "texture_common.h"

namespace gl {
	//! Texture image formats
	//! Format of the pixel data.
	//! Number of color components in the texture, values are taken from GL api
	//! FTODO: Digerlerini de ekleyelim
	enum class PixelType : uint32_t {
		UNSIGNED_BYTE = 0x1401,

		//! Extensions
		SHORT_5_6_5 = 0x8363,
		SHORT_5_5_5_1 = 0x8034,
		SHORT_4_4_4_4 = 0x8033,
	};
}

#endif	// INC_PIXEL_TYPE_H

/**
Copyright (c) [2023][Yazilimperver - yazilimpervergs@gmail.com]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */


