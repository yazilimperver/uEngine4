/**
 * @file   envelope.h
 * @date   4/24/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_ENVELOPE_H
#define INC_ENVELOPE_H

#include "glm/glm.hpp"

//! Envelope that surround basic geometries
class Envelope
{
public:
	Envelope();
		
	Envelope(float minx, float miny,
		float maxx, float maxy);

	bool IsValid() const;
	bool IsContains(const glm::vec2& point) const;
	bool IsContains(const glm::vec3& point) const;
	bool IsContains(const Envelope& envelope) const;
	bool IsIntersects(const Envelope& envelope) const;

	void SetEnvelope(float minX, float minY, float maxX, float maxY);

	Envelope GetIntersected(const Envelope& envelope) const;
	glm::vec2 GetCenter() const;

	float GetWidth() const;
	float GetHeight() const;
	float GetLeft() const;
	float GetRight() const;
	float GetTop() const;
	float GetBottom() const;

protected:
	//! Envelope points
	glm::vec2 mMinPoint;
	glm::vec2 mMaxPoint;
};

#endif	// INC_ENVELOPE_H

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


