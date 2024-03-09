#include "point.h"

extern bool IsEqual(double first, double second);

Point::Point() : mPoint{ 0.0F, 0.0F }{
}

Point::Point(const glm::dvec2& pnt) : mPoint{ pnt }
{

}

Point::Point(double x, double y) : mPoint{ x, y }
{

}

double Point::GetX() const
{
	return mPoint.x;
}

double Point::GetY() const
{
	return mPoint.y;
}

void Point::SetXY(double x, double y)
{
	mPoint.x = x;
	mPoint.y = y;
}

void Point::SetX(double x)
{
	mPoint.x = x;
}

void Point::SetY(double y)
{
	mPoint.y = y;
}

glm::dvec2 Point::GetPoint() const
{
	return mPoint;
}

void Point::SetPoint(const glm::dvec2& point)
{
	mPoint = point;
}

double Point::GetAngle(const Point& pnt) const
{
	return atan2(pnt.mPoint[1] - mPoint[1], pnt.mPoint[0] - mPoint[0]);
}

double Point::GetDistance(const Point& pnt) const
{
	double diffX = (pnt.mPoint[0] - mPoint[0]);
	double diffY = (pnt.mPoint[1] - mPoint[1]);

	return sqrt(diffX*diffX + diffY*diffY);
}

Point Point::ShiftPoint(double angleInRad, double distance) const
{
	Point pointToShift;
	pointToShift.SetX(distance*cos(angleInRad) + mPoint.x);
	pointToShift.SetY(distance*sin(angleInRad) + mPoint.y);

	return pointToShift;
}

glm::dvec2* Point::GetPointPtr()
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

double Point::operator*(const Point& rhs) const
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

const Point Point::operator*(const double value) const
{
	return Point(mPoint[0] * value, mPoint[1] * value);
}

const Point Point::operator/(const double denumerator) const
{
	return Point(mPoint[0] / denumerator, mPoint[1] / denumerator);
}