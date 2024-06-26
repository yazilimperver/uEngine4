/**
 * @file   brush_style.h
 * @date   4/23/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_BRUSH_STYLE_H
#define INC_BRUSH_STYLE_H

namespace gl {
	//! Firca stili icin kullanilacaktir
	enum class BrushStyle : int32_t {
		NoBrush,
		SolidPattern,
		HalfTonePattern,
		DotPattern,
		LinePattern,
		DensePattern,
		DashPattern,
		CheckPattern,
		CrossPattern,
		HorizontalPattern,
		VerticalPattern,
		BackwardDiagonalPattern,
		ForwardDiagonalPattern,
		DiagonalCrossPattern
	};
}

#endif	// INC_BRUSH_STYLE_H

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


