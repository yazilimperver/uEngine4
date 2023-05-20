#include "point.h"

extern bool IsEqual(float first, float second);

Point::Point() : mPoint{ 0.0F, 0.0F }{
}

Point::Point(const glm::vec2& pnt) : mPoint{ pnt }
{

}

Point::Point(float x, float y) : mPoint{ x, y }
{

}

float Point::GetX() const
{
	return mPoint.x;
}

float Point::GetY() const
{
	return mPoint.y;
}

void Point::SetXY(float x, float y)
{
	mPoint.x = x;
	mPoint.y = y;
}

void Point::SetX(float x)
{
	mPoint.x = x;
}

void Point::SetY(float y)
{
	mPoint.y = y;
}

glm::vec2 Point::GetPoint() const
{
	return mPoint;
}

void Point::SetPoint(const glm::vec2& point)
{
	mPoint = point;
}

float Point::GetAngle(const Point& pnt) const
{
	return atan2(pnt.mPoint[1] - mPoint[1], pnt.mPoint[0] - mPoint[0]);
}

float Point::GetDistance(const Point& pnt) const
{
	float diffX = (pnt.mPoint[0] - mPoint[0]);
	float diffY = (pnt.mPoint[1] - mPoint[1]);

	return sqrt(diffX*diffX + diffY*diffY);
}

Point Point::ShiftPoint(float angleInRad, float distance) const
{
	Point pointToShift;
	pointToShift.SetX(distance*cos(angleInRad) + mPoint.x);
	pointToShift.SetY(distance*sin(angleInRad) + mPoint.y);

	return pointToShift;
}

glm::vec2* Point::GetPointPtr()
{
	return &mPoint;
}

bool Point::operator==(const Point& point)
{
	return (IsEqual(mPoint[0], point.mPoint[0]) &&
		IsEqual(mPoint[1], point.mPoint[1]));
}

bool Point::operator!=(const Point& point)
{
	return !(*this == point);
}

Point& Point::operator+=(const Point& point)
{
	mPoint[0] += point.mPoint[0];
	mPoint[1] += point.mPoint[1];
	return *this;
}

const Point Point::operator-() const
{
	return Point(-mPoint[0], -mPoint[1]);
}

float Point::operator*(const Point& rhs) const
{
	return mPoint[0] * rhs.mPoint[0] + mPoint[1] * rhs.mPoint[1] + mPoint[2] * rhs.mPoint[2];
}

const Point Point::operator-(const Point& point) const
{
	return Point(mPoint[0] - point.GetX(), mPoint[1] - point.GetY());
}

const Point Point::operator+(const Point& point) const
{
	return Point(mPoint[0] + point.GetX(), mPoint[1] + point.GetY());
}

const Point Point::operator*(const float value) const
{
	return Point(mPoint[0] * value, mPoint[1] * value);
}

const Point Point::operator/(const float denumerator) const
{
	return Point(mPoint[0] / denumerator, mPoint[1] / denumerator);
}