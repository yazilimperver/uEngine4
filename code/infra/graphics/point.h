/**
 * @file   point.h
 * @date   4/25/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_POINT_H
#define INC_POINT_H

#include "glm/glm.hpp"

class Point {
public:
	Point();
	Point(const glm::dvec2& pnt);
	Point(double x, double y);

	double GetX() const;
	double GetY() const;
	
	void SetXY(double x, double y);
	void SetX(double x);
	void SetY(double y);

	glm::dvec2 GetPoint() const;

	void SetPoint(const glm::dvec2& point);

	// Calculates the angle (in RADIAN) of the vector which has the start point as this point and end point pnt
	// Note that this not consider great circle calculation
	double GetAngle(const Point& pnt) const;

	// Return the direct distance of this point to given pnt
	// Note that this not consider great circle calculation
	double GetDistance(const Point& pnt) const;

	// Shift the point in the given direction
	// angle is in radian
	Point ShiftPoint(double angleInRad, double distance) const;

	const Point operator / (const double denumerator) const;
	const Point operator * (const double value) const;
	const Point operator + (const Point& point) const;
	const Point operator - (const Point& point) const;
	const Point operator - () const;
	double operator * (const Point& rhs) const;

	Point& operator += (const Point& point);		
	bool operator != (const Point& point);
	bool operator == (const Point& point);
		
	glm::dvec2* GetPointPtr();

protected:
	//! The point data
	glm::dvec2 mPoint;
};

#endif	// INC_POINT_H

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

