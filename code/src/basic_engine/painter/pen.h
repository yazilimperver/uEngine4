/**
 * @file pen.h.
 * @date 9.08.2022
 * @author Yazilimperver
 * @brief  Cizim stilini belirlemek icin kullanlacak olan siniftir.
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef PEN
#define PEN

#include <cstdint>

#include "graphics/color.h"

namespace basic_engine {
	class Pen {
	public:
		Pen();
		explicit Pen(const Color& color);
		Pen(const Color& color,
			uint8_t width,
			const Color& strokeColor = Color::Black,
			uint8_t strokeWidth = 0.0F);
		void SetWidth(uint8_t width);
		uint8_t Width() const;
		void SetStrokeWidth(uint8_t width);
		uint8_t StrokeWidth() const;

		void SetColor(const Color& color);
		Color PenColor() const;
		void SetStrokeColor(const Color& color);
		Color StrokeColor() const;
	protected:
		uint8_t mWidth;
		uint8_t mStrokeWidth;
		Color mColor;
		Color mStrokeColor;
	};
}
#endif // !PEN

/**
Copyright (c) [2022][Yazilimperver - yazilimpervergs@gmail.com]

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
