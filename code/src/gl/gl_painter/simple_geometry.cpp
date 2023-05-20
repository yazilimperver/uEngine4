#include "simple_geometry.h"

namespace gl {	
	SimpleGeometry::SimpleGeometry(GeometryType geometryType) : mGeometryType{ geometryType }	{

	}

	gl::GeometryType SimpleGeometry::GetGeometryType() const {
		return mGeometryType;
	}

	void SimpleGeometry::SetGeometryType(GeometryType val) {
		mGeometryType = val;
	}

	void SimpleGeometry::SetPoint(uint32_t index, const glm::vec3& pnt)	{
		if (index < mGeometryPoints.size()) {
			mGeometryPoints[index] = pnt;
		}
	}

	std::optional<glm::vec3> SimpleGeometry::GetPoint3D(uint32_t index) const	{
		if (index < mGeometryPoints.size()) {
			return mGeometryPoints[index];
		}
		else {
			return std::nullopt;
		}
	}

	std::optional<glm::vec2>  SimpleGeometry::GetPoint2D(uint32_t index) const	{
		if (index < mGeometryPoints.size()) {
			glm::vec2 pnt;
			pnt.x = mGeometryPoints[index].x;
			pnt.y = mGeometryPoints[index].y;

			return pnt;
		}
		else {
			return std::nullopt;
		}
	}

	std::vector<glm::vec3>& SimpleGeometry::GetPoints()	{
		return mGeometryPoints;
	}

	const glm::vec3* SimpleGeometry::GetPointPtr() const {
		return &(mGeometryPoints[0]);
	}

	void SimpleGeometry::SetHasZ(bool hasZ)	{
		mHasZ = hasZ;
	}

	bool SimpleGeometry::IsHasZ() {
		return mHasZ;
	}

	const Envelope& SimpleGeometry::GetEnvelope() const	{
		return mEnvelope;
	}

	void SimpleGeometry::SetEnvelope(const Envelope& envelope)	{
		mEnvelope = envelope;
	}

	void SimpleGeometry::CalculateEnvelope() {
		float minX = FLT_MAX;
		float minY = FLT_MAX;
		float maxX = FLT_MIN;
		float maxY = FLT_MIN;

		for (const auto& point : mGeometryPoints) {
			if (minX > point.x)	{
				minX = point.x;
			}
			if (maxX < point.x)	{
				maxX = point.x;
			}
			if (minY > point.y) {
				minY = point.y;
			}
			if (maxY < point.y) {
				maxY = point.y;
			}
		}

		mEnvelope.SetEnvelope(minX, minY, maxX, maxY);
	}

	uint32_t SimpleGeometry::GetPointCount() const {
		return static_cast<uint32_t>(mGeometryPoints.size());
	}

	const float cConcavenessThreshold = 0.00001F;

	bool SimpleGeometry::CheckConvexness() const {
		bool isConvex = true;
		bool isPreviousMinus;
		bool isMinus;

		const uint32_t cMinNoOfPointsForConcaveTest = 4U;

		if (mGeometryPoints.size() > cMinNoOfPointsForConcaveTest) {
			glm::vec3 vec1;
			glm::vec3 vec2;
			glm::vec3 result;

			for (uint32_t i = 2; (true == isConvex) && (i < mGeometryPoints.size()); ++i) {
				vec1 = mGeometryPoints[i - 1U] - mGeometryPoints[i - 2];
				vec2 = mGeometryPoints[i] - mGeometryPoints[i - 1U];

				result = glm::cross(vec1, vec2);

				if (result.z < 0) {
					isMinus = true;
				}
				else {
					isMinus = false;
				}

				if (2 == i) {
					isPreviousMinus = isMinus;
				}

				if (glm::abs(result.z) > cConcavenessThreshold) {
					if ((i > 2)
						&&
						(isMinus != isPreviousMinus)) {
						isConvex = false;
					}
				}
			}
		}

		return isConvex;
	}

	bool SimpleGeometry::IsConvex() const {
		return mIsConvex;
	}

	void SimpleGeometry::SetIsConvex(bool val) {
		mIsConvex = val;
	}
}