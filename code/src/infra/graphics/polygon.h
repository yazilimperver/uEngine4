/**
 * @file   polygon.h
 * @date   4/25/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_POLYGON_H
#define INC_POLYGON_H

#include <cstdint>
#include <vector>
#include <optional>

#include "line.h"
#include "envelope.h"

class  Polygon {
public:
	uint32_t GetPointCount() const;
	std::optional<glm::vec2> GetPoint(uint16_t index) const;

	void Append(const glm::vec2& point);
	void RemoveLastPoint();
	void RemoveAt(uint16_t index);
	std::optional<Envelope> GetEnvelope();
	void CalculateEnvelope();
	bool Intersect(const Polygon& polygon);
	bool IsPointInsidePolygon(const glm::vec2& point);
	bool IsInsidePolygon(const glm::vec2& point);
	bool IsInsidePolygon(const Polygon& polygon);

	//calculates if polygon is convex/concave
	bool IsConvex() const;

	glm::vec2* GetPointPtr();
	void Clear();

	std::vector<glm::vec2>& GetPoints();
	void SetPoints(std::vector<glm::vec2> val);
protected:

private:
	std::vector<glm::vec2> mPoints;
	Envelope mEnvelope;
};

#endif	// INC_POLYGON_H

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


