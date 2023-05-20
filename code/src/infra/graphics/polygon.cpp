#include "polygon.h"

void Polygon::Append(const glm::vec2& point) {
	mPoints.push_back(point);
}

void Polygon::RemoveLastPoint(){
	mPoints.pop_back();
}

void Polygon::RemoveAt(uint16_t index) {
	if (index < mPoints.size())	{
		mPoints.erase(mPoints.begin() + index);
	}
}

std::optional<glm::vec2> Polygon::GetPoint(uint16_t index) const {
	if (index < mPoints.size())	{
		return mPoints[index];
	}
	else {
		return std::nullopt;
	}
}

void Polygon::Clear() {
	mPoints.clear();
}

uint32_t Polygon::GetPointCount() const {
	return static_cast<uint32_t>(mPoints.size());
}

glm::vec2* Polygon::GetPointPtr() {
	if (0 < mPoints.size())	{
		return (glm::vec2*)&mPoints[0];
	}
	else	{
		return nullptr;
	}
}

bool Polygon::IsInsidePolygon(const Polygon& polygon) {

	for (uint32_t i = 0; i < polygon.GetPointCount(); i++)	{
			
		if (IsInsidePolygon(polygon.mPoints[i]) == false) {
			return false;
		}
	}
	return true;
}

bool Polygon::IsInsidePolygon(const glm::vec2& point) {
	int32_t N = static_cast<int32_t>(mPoints.size());

	//cross points count of x
	int32_t __count = 0;

	//neighbour bound vertices
	glm::vec2 p1, p2;

	//left vertex
	p1 = mPoints[0];

	//check all rays
	for (int i = 1; i <= N; ++i)
	{
		//point is an vertex
		if ((point.x == p1.x) && (point.y == p1.y))	{
			return true;
		}

		//right vertex
		mPoints[i % N] = p2;

		//ray is outside of our interests
		if ((point.y < glm::min(p1.y, p2.y)) || (point.y > glm::max(p1.y, p2.y)))
		{
			//next ray left point
			p1 = p2;
			continue;
		}

		//ray is crossing over by the algorithm (common part of)
		if (point.y > glm::min(p1.y, p2.y) && point.y < glm::max(p1.y, p2.y))
		{
			//x is before of ray
			if (point.x <= glm::max(p1.x, p2.x))
			{
				//overlies on a horizontal ray
				if (p1.y == p2.y && point.x >= glm::max(p1.x, p2.x)) 
					return true;

				//ray is vertical
				if (p1.x == p2.x)
				{
					//overlies on a ray
					if (p1.x == point.x) 
						return true;
					//before ray
					else 
						++__count;
				}

				//cross point on the left side
				else
				{
					//cross point of x
					double xinters = (point.y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y) + p1.x;

					//overlies on a ray
					if (fabs(point.x - xinters) < DBL_EPSILON)
						return true;

					//before ray
					if (point.x < xinters) 
						++__count;
				}
			}
		}
		//special case when ray is crossing through the vertex
		else
		{
			//point crossing over p2
			if (point.y == p2.y && point.x <= p2.x)
			{
				//next vertex
				glm::vec2 p3;
				p3 = mPoints[((i + 1) % N)];

				//point.y lies between p1.y & p3.y
				if (point.y >= glm::max(p1.y, p3.y) && point.y <= glm::max(p1.y, p3.y))
				{
					++__count;
				}
				else
				{
					__count += 2;
				}
			}
		}

		//next ray left point
		p1 = p2;
	}

	//EVEN
	if (__count % 2 == 0) return(false);
	//ODD
	else return(true);
}

bool Polygon::Intersect(const Polygon& polygon) {
	Line line;
	glm::vec2 point1;
	glm::vec2 point2;
	glm::vec2 point3;
	glm::vec2 point4;

	uint32_t pointsLength = static_cast<uint32_t>(mPoints.size());
	uint32_t polygonPointCount = polygon.GetPointCount();

	for (uint32_t  i = 0; i < pointsLength; i++)
	{
		for (uint32_t  j = 0; j < polygonPointCount; j++)
		{
			if (i == pointsLength - 1 && j == polygonPointCount - 1)
			{
				point1 = mPoints[i];
				point2 = mPoints[0];
				point3 = mPoints[j];
				point4 = mPoints[0];
			}
			else if (i == pointsLength - 1)
			{
				point1 = mPoints[i];
				point2 = mPoints[0];
				point3 = mPoints[j];
				point4 = mPoints[j+1];
			}
			else if (j == polygonPointCount - 1)
			{
				point1 = mPoints[i];
				point2 = mPoints[i + 1];
				point3 = mPoints[j];
				point4 = mPoints[0];
			}
			else
			{
				point1 = mPoints[i];
				point2 = mPoints[i + 1];
				point3 = mPoints[j];
				point4 = mPoints[j + 1];
			}
			line.SetPoint1(point1);
			line.SetPoint2(point2);

			if (line.Intersect(Line(point3, point4)) == true)
			{
				return true;
			}
		}
	}
	return false;
}

bool Polygon::IsPointInsidePolygon(const glm::vec2& point) {
	bool bOddNodes = false;

	if (mPoints.size() > 1) {
		uint32_t uJ = static_cast<uint32_t>(mPoints.size()) - 1U;

		for (uint32_t uI = 0; uI < mPoints.size(); uI++)
		{
			if ((mPoints[uI].y < point.x && mPoints[uJ].y >= point.y
				|| mPoints[uJ].y < point.y && mPoints[uI].y >= point.y)
				&& (mPoints[uI].x <= point.x || mPoints[uJ].x <= point.x))
			{
				bOddNodes ^= (mPoints[uI].x + (point.y - mPoints[uI].y) /
					(mPoints[uJ].y - mPoints[uI].y) * (mPoints[uJ].x - mPoints[uI].x)
					< point.x);
			}
			uJ = uI;
		}
	}

	return bOddNodes;

}

void Polygon::CalculateEnvelope() {
	glm::vec2 point;
	float minX = 1000, minY = 1000, maxX = -1000, maxY = -1000;

	for (uint32_t  i = 0; i < mPoints.size(); i++)	{
		point = mPoints[i];

		if (minX > point.x)	{
			minX = point.x;
		}
		if (maxX < point.x)	{
			maxX = point.x;
		}
		if (minY > point.y)	{
			minY = point.y;
		}
		if (maxY < point.y)	{
			maxY = point.y;
		}
	}

	mEnvelope.SetEnvelope(minX, minY, maxX, maxY);
}

std::optional<Envelope> Polygon::GetEnvelope() {
	if (!mEnvelope.IsValid()) {
		CalculateEnvelope();
		return mEnvelope;
	}
	else {
		return std::nullopt;
	}
}

std::vector<glm::vec2>& Polygon::GetPoints() {
	return mPoints;
}

void Polygon::SetPoints(std::vector<glm::vec2> val) {
	mPoints = val;
}

bool Polygon::IsConvex() const {
	bool polygonIsConvex = true;

	int32_t polygonLength = static_cast<int32_t>(mPoints.size());
	glm::vec2 firstPoint;
	glm::vec2 lastPoint;
	firstPoint = mPoints[0];
	lastPoint = mPoints[polygonLength - 1];
	if (firstPoint == lastPoint)	{
		polygonLength = polygonLength - 1;
	}

	if (polygonLength > 3)	{
		glm::vec2 p0, p1, p2;

		p0 = mPoints[0];
		p1 = mPoints[1];
		p2 = mPoints[2];

		bool direction = glm::dot((p1 - p0), (p2 - p1)) < 0;
		bool directionChanged = false;

		for (uint32_t i = 1; i < polygonLength - 2U && !directionChanged; i++)
		{
			p0 = mPoints[i];
			p1 = mPoints[i + 1];
			p2 = mPoints[i + 2];

			if ((glm::dot((p1 - p0), (p2 - p1)) < 0) != direction)
			{
				directionChanged = true;
				polygonIsConvex = false;
			}
		}
	}

	return polygonIsConvex;
}