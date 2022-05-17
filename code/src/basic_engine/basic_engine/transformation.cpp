#include "transformation.h"

namespace basic_engine {
	void Transformation::Move(float offsetX, float offsetY) {
		mPosition.x += offsetX;
		mPosition.y += offsetY;
	}

	void Transformation::SetPosition(float posX, float posY) {
		mPosition.x = posX;
		mPosition.y = posY;
	}

	const Vector2f& Transformation::Pos() const {
		return mPosition;
	}

	void Transformation::Reset() {
		mOrigin.x = 0;
		mOrigin.y = 0;
		mRotation = 0;
		mScale.x = 0;
		mScale.y = 0;
	}

	void Transformation::Rotate(float angle) {
		mRotation = angle;
	}

	void Transformation::Scale(const Vector2f& scale) {
		mScale = scale;
	}
}