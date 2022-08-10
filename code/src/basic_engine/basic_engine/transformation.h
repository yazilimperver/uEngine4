/**
 * @file transformation.h.
 * @date 12.05.2022
 * @author Yazilimperver
 * @brief Temel 2B transformasyon durumunu tutan sýnýftýr
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */

#ifndef TRANSFORMATION
#define TRANSFORMATION

#include "common.h"

namespace basic_engine {
	class Transformation {
	public:
		float Rotation() const;
		const Vector2i& Pos() const;
		const Vector2f& Scale() const;
		const Vector2i& Origin() const;

		void Reset();
		void Rotate(float angle);
		void SetScale(const Vector2f& scale);
		void Move(int32_t offsetX, int32_t offsetY);
		void SetPosition(int32_t posX, int32_t posY);
	protected:
		/** @brief Tasima, donme ve olceklendirme icin referans alinacak noktadir */
		Vector2i mOrigin{0,0};
		Vector2i mPosition{0, 0};
		Vector2f mScale{1, 1};
		float mRotation{ 0.0f };
	};
}

#endif // !TRANSFORMABLE

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
