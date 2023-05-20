/**
 * @file   brush.h
 * @date   4/23/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_BRUSH_H
#define INC_BRUSH_H

#include <cstdint> 

#include "brush_style.h"
#include "graphics/color.h"

namespace gl
{
    class Brush
    {
	public:
		Brush();
		Brush(const Color& color, BrushStyle brushStyle = BrushStyle::SolidPattern);

		~Brush(void);

		Color GetColor() const;
		void SetColor(Color color);

		BrushStyle GetStyle() const;
		void SetStyle(BrushStyle brushStyle);
		
		bool operator==(const Brush& rhs);
		bool operator!=(const Brush& rhs);
	private:
		Color mColor;
		BrushStyle mStyle;
    };
}

#endif	// INC_BRUSH_H

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


