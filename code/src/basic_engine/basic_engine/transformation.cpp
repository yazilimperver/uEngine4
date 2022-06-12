#include "transformation.h"

namespace basic_engine {
	void Transformation::Move(int32_t offsetX, int32_t offsetY) {
		mPosition.x += offsetX;
		mPosition.y += offsetY;
	}

	void Transformation::SetPosition(int32_t posX, int32_t posY) {
		mPosition.x = posX;
		mPosition.y = posY;
	}

	const Vector2i& Transformation::Pos() const {
		return mPosition;
	}

	float Transformation::Rotation() const {
		return mRotation;
	}

	const Vector2f& Transformation::Scale() const {
		return mScale;
	}

	const Vector2i& Transformation::Origin() const {
		return mOrigin;
	}

	void Transformation::Reset() {
		mOrigin.x = 0;
		mOrigin.y = 0;
		mRotation = 0;
		mScale.x = 1;
		mScale.y = 1;
	}

	void Transformation::Rotate(float angle) {
		mRotation = angle;
	}

	void Transformation::SetScale(const Vector2f& scale) {
		mScale = scale;
	}
}