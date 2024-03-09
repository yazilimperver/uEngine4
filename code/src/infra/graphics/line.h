/**
 * @file   line.h
 * @date   4/25/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_LINE_H
#define INC_LINE_H

#include "glm/glm.hpp"
#include "intersection_result.h"
#include "projection_result.h"

class  Line {
public:
	Line(void);
	Line(const glm::dvec2& point1, const glm::dvec2& point2);
	Line(double x1,
		double y1,
		double x2,
		double y2);
	~Line(void);

	glm::dvec2 GetPoint1() const;
	glm::dvec2 GetPoint2() const;
	void SetPoint1(const glm::dvec2& point);
	void SetPoint2(const glm::dvec2& point);

	// use the line itself given point and return
	// projection result, intersection point and proportion of projected point on line
	// [0, 1] in case of within, outside otherwise
	ProjectionResult Project(glm::dvec2& pointToProject,
		glm::dvec2& intersectionPoint,
		double& proportion);

	double GetX1() const;
	double GetX2() const;
	double GetY1() const;
	double GetY2() const;

	double InnerProduct(const Line line);

	void SetPoints(const glm::dvec2& point1, const glm::dvec2& point2);
	void SetLine(double x1,
		double y1,
		double x2,
		double y2);
	bool Intersect(const Line& otherLine);
	bool Intersect(const glm::dvec2& center, double dRadius);
	IntersectionResult Intersect(const Line& otherLine, glm::dvec2& intersection);

	glm::dvec2 GetMidPoint();

protected:
	double Magnitude(const glm::dvec2& point1, const glm::dvec2& point2);

	//! Line start point
	glm::dvec2 mPoint1;

	//! Line end point
	glm::dvec2 mPoint2;
};

#endif	// INC_LINE_H

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


