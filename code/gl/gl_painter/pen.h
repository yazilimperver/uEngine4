/**
 * @file   pen.h
 * @date   4/23/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_PEN_H
#define INC_PEN_H

#include <cstdint>

#include "graphics/color.h"

#include "pen_style.h"

namespace gl {
    class Pen {
	public:
		Pen();
		explicit Pen(const Color& color);

        // TODO: Argumanlari strok ile benzer sira yapalim
		Pen(PenStyle penStyle,
			const Color& color,
			float width,
			int32_t styleFactor = 1,
			const Color& strokeColor = Color(Color::Black),
			PenStyle strokeStyle = PenStyle::SolidLine,
			float strokeWidth = 0.0F);

		~Pen(void);
		bool HasStroke() const;

		int32_t GetStyleFactor() const;
		void SetStyleFactor(int32_t factor);

		PenStyle GetPenStyle(bool isStroke = false) const;
		void SetPenStyle(PenStyle penStyle, bool isStroke = false);

		float GetWidth(bool isStroke = false) const;
		void SetWidth(float width, bool isStroke = false);

		Color GetColor(bool isStroke = false) const;
		void SetColor(const Color& color, bool isStroke = false);

		bool operator==(const Pen& rhs);
		bool operator!=(const Pen& rhs);
	private:
		//! Is provided to glLineStipple
		int32_t mStyleFactor;
		PenStyle mPenStyle;
		PenStyle mStrokePenStyle;
		float mWidth;
		float mStrokeWidth;
		Color mColor;
		Color mStrokeColor;
    };
}

#endif	// INC_PEN_H

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