/**
 * @file   polygon_triangulator.h
 * @date   4/25/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_POLYGON_TRIANGULATOR_H
#define INC_POLYGON_TRIANGULATOR_H

#include <vector>

#include "glm/glm.hpp"

class PolygonTriangulator {
public:
	static bool Triangulate(const std::vector<glm::vec2>& polygon, std::vector<glm::vec2>& triangulatedTriangles);

private:
	// compute area of a contour/polygon
	static float GetArea(const std::vector<glm::vec2>& contour);

	// decide if point Px/Py is inside triangle defined by
	// (Ax,Ay) (Bx,By) (Cx,Cy)
	static bool IsInsideTriangle(const glm::vec2& A,
		const glm::vec2& B,
		const glm::vec2& C,
		const glm::vec2& P);


	static bool Snip(const std::vector<glm::vec2>& contour,
		int32_t  u,
		int32_t  v,
		int32_t  w,
		int32_t  n,
		int32_t* V);
};

#endif	// INC_POLYGON_TRIANGULATOR_H

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


