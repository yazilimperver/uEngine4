/**
 * @file transformation.h.
 * @date 12.05.2022
 * @author Yazilimperver
 * @brief 
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */

#ifndef TRANSFORMATION
#define TRANSFORMATION

#include "common.h"

namespace basic_engine {
	class Transformation {
	public:
		const Vector2f& Pos() const;
		void Reset();
		void Rotate(float angle);
		void Scale(const Vector2f& scale);
		void Move(float offsetX, float offsetY);
	protected:
		/** @brief Tasima, donme ve olceklendirme icin referans alinacak noktadir */
		Vector2f mOrigin{0,0};
		Vector2f mPosition{ 0,0 };
		float mRotation{ 0.0f };
		Vector2f mScale{ 0,0 };
	};
}

#endif // !TRANSFORMABLE