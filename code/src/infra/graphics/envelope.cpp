#include "envelope.h"

Envelope::Envelope() : mMinPoint{ 0.0f, 0.0f },
	mMaxPoint{ 0.0f, 0.0f } {

}

Envelope::Envelope(float minx, float miny, float maxx, float maxy) {
	mMinPoint.x = minx;
	mMinPoint.y = miny;

	mMaxPoint.x = maxx;
	mMaxPoint.y = maxy;
}

bool Envelope::IsValid() const {
	if ((mMinPoint.x > 0) && (mMaxPoint.x > 0) && (mMinPoint.y > 0) && (mMaxPoint.y > 0))
	{
		return true;
	}

	return false;
}

void Envelope::SetEnvelope(float minX, float minY, float maxX, float maxY) {
	mMinPoint.x = minX;
	mMinPoint.y = minY;
	mMaxPoint.x = maxX;
	mMaxPoint.y = maxY;

	if (mMinPoint.x > mMaxPoint.x)
	{
		float swap = mMinPoint.x;
		mMinPoint.x = mMaxPoint.x;
		mMaxPoint.x = swap;
	}

	if (mMinPoint.y > mMaxPoint.y)
	{
		float swap = mMinPoint.y;
		mMinPoint.y = mMaxPoint.y;
		mMaxPoint.y = swap;
	}
}

bool Envelope::IsContains(const glm::vec2& point) const {
	bool result = true;

	if ((point.x > mMaxPoint.x) ||
		(point.x < mMinPoint.x) ||
		(point.y > mMaxPoint.y) ||
		(point.y < mMinPoint.y))
	{
		result = false;
	}

	return result;
}

bool Envelope::IsContains(const glm::vec3& point) const {
	bool result = true;

	if ((point.x > mMaxPoint.x) ||
		(point.x < mMinPoint.x) ||
		(point.y > mMaxPoint.y) ||
		(point.y < mMinPoint.y))
	{
		result = false;
	}

	return result;
}

bool Envelope::IsContains(const Envelope& envelope) const {
	bool result = false;

	if ((mMinPoint.x <= envelope.mMinPoint.x) &&
		(mMaxPoint.x >= envelope.mMaxPoint.x) &&
		(mMinPoint.y <= envelope.mMinPoint.y) &&
		(mMaxPoint.y >= envelope.mMaxPoint.y))
	{
		result = true;
	}

	return result;
}

bool Envelope::IsIntersects(const Envelope& envelope) const {
	bool result = true;

	if ((mMinPoint.x > envelope.mMaxPoint.x) ||
		(mMaxPoint.x < envelope.mMinPoint.x) ||
		(mMinPoint.y > envelope.mMaxPoint.y) ||
		(mMaxPoint.y < envelope.mMinPoint.y))
	{
		result = false;
	}

	return result;
}

Envelope Envelope::GetIntersected(const Envelope& envelope) const {
	Envelope result;

	if (IsIntersects(envelope))
	{
		result = *this;

		if (envelope.mMinPoint.x > result.mMinPoint.x)
		{
			result.mMinPoint.x = envelope.mMinPoint.x;
		}

		if (envelope.mMaxPoint.x < result.mMaxPoint.x)
		{
			result.mMaxPoint.x = envelope.mMaxPoint.x;
		}

		if (envelope.mMinPoint.y > result.mMinPoint.y)
		{
			result.mMinPoint.y = envelope.mMinPoint.y;
		}

		if (envelope.mMaxPoint.y < result.mMaxPoint.y)
		{
			result.mMaxPoint.y = envelope.mMaxPoint.y;
		}
	}

	return result;
}

glm::vec2 Envelope::GetCenter() const {
	return (mMinPoint + mMaxPoint) * 0.5f;
}

float Envelope::GetWidth() const {
	return (mMaxPoint.x - mMinPoint.x);
}

float Envelope::GetHeight() const {
	return (mMaxPoint.y - mMinPoint.y);
}

float Envelope::GetLeft() const {
	return mMinPoint.x;
}

float Envelope::GetRight() const {
	return mMaxPoint.x;
}

float Envelope::GetTop() const {
	return mMaxPoint.y;
}

float Envelope::GetBottom() const {
	return mMinPoint.y;
}