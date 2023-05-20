/**
 * @file   simple_geometry.h
 * @date   4/23/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_SIMPLE_GEOMETRY_H
#define INC_SIMPLE_GEOMETRY_H

#include <vector>
#include <optional>

#include "glm/glm.hpp"

#include "graphics/envelope.h"
#include "geometry_type.h"

namespace gl {

	//! Will be used for 2D rendering both for geographic and Cartesian points
    class SimpleGeometry {
	public:
		explicit SimpleGeometry(GeometryType geometryType);

		GeometryType GetGeometryType() const;

		void SetGeometryType(GeometryType val);

		void SetPoint(uint32_t index, const glm::vec3& pnt);
		std::optional<glm::vec3> GetPoint3D(uint32_t index = 0) const;
		std::optional<glm::vec2> GetPoint2D(uint32_t index = 0) const;

		std::vector<glm::vec3>& GetPoints();
		const glm::vec3* GetPointPtr() const;

		void SetHasZ(bool hasZ);
		bool IsHasZ();

		const Envelope& GetEnvelope() const;
		void SetEnvelope(const Envelope& envelope);

		void CalculateEnvelope();

		uint32_t  GetPointCount() const;
		
		// Check geometry's convexity
		bool CheckConvexness() const;

		// Return the calculated convexity of polygon 
		bool IsConvex() const;

		void  SetIsConvex(bool val);

	protected:

		/** @brief   Type of the geometry */
		GeometryType mGeometryType;

		/** @brief   True if has z coordinate, false if not */
		bool mHasZ;

		/** @brief   True if is convex, false if not */
		bool mIsConvex;

		/** @brief   Envelope of this geometry */
		Envelope mEnvelope;

		/** @brief   The point array */
		std::vector<glm::vec3> mGeometryPoints;
    };
}

#endif	// INC_SIMPLE_GEOMETRY_H

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


