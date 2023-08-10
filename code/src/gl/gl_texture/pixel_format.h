/**
 * @file   pixel_format.h
 * @date   5/22/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_PIXEL_FORMAT_H
#define INC_PIXEL_FORMAT_H

#include "texture_common.h"

namespace gl {
	//! Texture pixel internal formats
	enum class PixelFormat : uint32_t	{
		//! 4 bpp, 
		RGBA = 0x1908,
		PIXEL_FORMAT_GL_COMPRESSED_RGBA_S3TC_DXT3_EXT = 0x83F2,
		PIXEL_FORMAT_GL_COMPRESSED_RGBA_S3TC_DXT5_EXT = 0x83F3,

		//! 3 bpp
		RGB = 0x1907,
		PIXEL_FORMAT_GL_COMPRESSED_RGB_S3TC_DXT1_EXT = 0x83F0,
		PIXEL_FORMAT_GL_COMPRESSED_RGBA_S3TC_DXT1_EXT = 0x83F1,

		//! 2 bpp
		LUMINANCE_ALPHA = 0x190A,

		//! 1 bpp
		LUMINANCE = 0x1909,
		ALPHA = 0x1906,
	};
}

#endif	// INC_PIXEL_FORMAT_H

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


