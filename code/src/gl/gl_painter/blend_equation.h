/**
 * @file   blend_equation.h
 * @date   4/20/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_BLEND_EQUATION_H
#define INC_BLEND_EQUATION_H

#include <cstdint>

namespace gl {
    /**
     * @enum    uBlendEquation
     *
     * @brief    brief Enumeration of the blending equations
     *          
     *           The equations are mapped directly to their OpenGL equivalents, specified by
     *           glBlendEquation() or glBlendEquationSeparate().
     */
    enum class uBlendEquation : int32_t {
		Add = 0x8006,            ///< Pixel = Src * SrcFactor + Dst * DstFactor
		Subtract = 0x800A,       ///< Pixel = Src * SrcFactor - Dst * DstFactor
		ReverseSubtract = 0x800B ///< Pixel = Dst * DstFactor - Src * SrcFactor
    };
}

#endif	// INC_BLEND_EQUATION_H

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


