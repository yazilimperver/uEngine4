/**
 * @file   color_ramp.h
 * @date   4/23/2023
 * @author Yazilimperver
 * @brief  Rolyef harita ya da analiz ciktilarinin renklendirilmesi icin kullanilabilecek siniftir.
 *         Renkler arasi interpolasyon yapilir.
 * @remark
 */

#ifndef INC_COLOR_RAMP_H
#define INC_COLOR_RAMP_H

#include "graphics/color.h"

#include <vector>

namespace gl {
    class ColorRamp {
		ColorRamp(int32_t maxColorTableSize = 1024);

        /** @brief   Colorramp için verilen degere renk eklenir */
		void AddColor(int32_t value, const Color& color);

        /** @brief   Interpole edilen renk donulur */
		void GetColor(int32_t value, Color& color);
	private:
		void GenerateColorTable();

		/** @brief   En fazla izin verilen renk adeti */
		int32_t mMaxColorTableSize;

		/** @brief   Interpolasyon icin kullanilacak irtifa degerleri */
		std::vector<int32_t> mAltitudeValues;

		/** @brief   Interpolasyon icin kullanilacak ana irtifa renkler */
		std::vector<Color> mColors;

		/** @brief   Ana irtifa renkleri arasini doldurmak icin kullanilacak renkler */
		std::vector<Color> mColorTable;

		/** @brief   Min/maksimum degerler. */
		double mMinValue;
		double mMaxValue;
		double mMaxMindDiffValue;
    };
}

#endif	// INC_COLOR_RAMP_H

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


