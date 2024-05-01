/**
 * @file   blend_factor.h
 * @date   4/20/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_BLEND_FACTOR_H
#define INC_BLEND_FACTOR_H

#include <cstdint>
namespace gl {

    /**
     * @enum    uBlendFactor
     *
     * @brief   \brief Enumeration of the blending factors The factors are mapped directly to their
     *          OpenGL equivalents, specified by glBlendFunc() or
     *          glBlendFuncSeparate().//////////////////////////////////////////////////////
     */
    enum class uBlendFactor  : int32_t 	{
		ZERO = 0,                  ///< (0, 0, 0, 0)
		ONE = 1,                   ///< (1, 1, 1, 1)
		SRCCOLOR = 0x0300,         ///< (src.r, src.g, src.b, src.a)
		ONEMINUSSRCCOLOR = 0x0301, ///< (1, 1, 1, 1) - (src.r, src.g, src.b, src.a)
		DSTCOLOR = 0x0306,         ///< (dst.r, dst.g, dst.b, dst.a)
		ONEMINUSDSTCOLOR = 0x0307, ///< (1, 1, 1, 1) - (dst.r, dst.g, dst.b, dst.a)
		SRCALPHA = 0x0302,         ///< (src.a, src.a, src.a, src.a)
		ONEMINUSSRCALPHA = 0x0303, ///< (1, 1, 1, 1) - (src.a, src.a, src.a, src.a)
		DSTALPHA = 0x0304,         ///< (dst.a, dst.a, dst.a, dst.a)
		ONEMINUSDSTALPHA = 0x0305  ///< (1, 1, 1, 1) - (dst.a, dst.a, dst.a, dst.a)
    };
}

#endif	// INC_BLEND_FACTOR_H

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


