#include "line.h"

#include <limits>

Line::Line(void)
	: mPoint1(0, 0)
	, mPoint2(0, 0)
{
}

Line::Line(const glm::dvec2& point1, const glm::dvec2& point2)
	: mPoint1(point1)
	, mPoint2(point2)
{

}

Line::Line(double x1,
	double y1,
	double x2,
	double y2)
	: mPoint1(x1, y1)
	, mPoint2(x2, y2)
{

}

Line::~Line(void)
{
}

void Line::SetPoints(const glm::dvec2& point1, const glm::dvec2& point2)
{
	mPoint1 = point1;
	mPoint2 = point2;
}

void Line::SetLine(double x1,
	double y1,
	double x2,
	double y2)
{
	mPoint1.x = x1;
	mPoint1.y = y1;
	mPoint2.x = x2;
	mPoint2.y = y2;
}

glm::dvec2 Line::GetPoint1() const
{
	return mPoint1;
}

void Line::SetPoint1(const glm::dvec2& point)
{
	mPoint1 = point;
}

glm::dvec2 Line::GetPoint2() const
{
	return mPoint2;
}

void Line::SetPoint2(const glm::dvec2& point)
{
	mPoint2 = point;
}

double Line::GetX1() const
{
	return mPoint1.x;
}

double Line::GetX2() const
{
	return mPoint2.x;
}

double Line::GetY1() const
{
	return mPoint1.y;
}

double Line::GetY2() const
{
	return mPoint2.y;
}

double Line::Magnitude(const glm::dvec2& point1, const glm::dvec2& point2)
{
	glm::dvec2 pointDiff = point2 - point1;
	double result = sqrt(pointDiff.x * pointDiff.x
		+ pointDiff.y * pointDiff.y);

	return result;
}

glm::dvec2 Line::GetMidPoint()
{
	return (mPoint1 + mPoint2) * 0.5;
}

double Line::InnerProduct(const Line line)
{
	glm::dvec2 pointDiff1 = mPoint2 - mPoint1;
	glm::dvec2 pointDiff2 = line.mPoint2 - line.mPoint1;

	return pointDiff1.x * pointDiff2.x + pointDiff1.y * pointDiff2.y;
}

bool Line::Intersect(const glm::dvec2& center, double dRadius)
{
	Line lineF(center, mPoint1);

	double dAValue = InnerProduct((*this));

	double dBValue = 2.0F * lineF.InnerProduct((*this));
	double dCValue = lineF.InnerProduct(lineF) - dRadius * dRadius;

	double dDiscriminant = dBValue * dBValue - 4.0 * dAValue * dCValue;

	if (dDiscriminant < 0.0)
	{
		return false;
		// no intersection
	}
	else
	{
		// ray didn't totally miss sphere,
		// so there is a solution to
		// the equation.
		dDiscriminant = sqrt(dDiscriminant);

		// either solution may be on or off the ray so need to test both
		// t1 is always the smaller value, because BOTH discriminant and
		// a are nonnegative.
		double dRoot1 = (-dBValue - dDiscriminant) / (2.0 * dAValue);
		double dRoot2 = (-dBValue + dDiscriminant) / (2.0 * dAValue);

		// 3x HIT cases:
		//          -o->             --|-->  |            |  --|->
		// Impale(t1 hit,t2 hit), Poke(t1 hit,t2>1), ExitWound(t1<0, t2 hit), 

		// 3x MISS cases:
		//       ->  o                     o ->              | -> |
		// FallShort (t1>1,t2>1), Past (t1<0,t2<0), CompletelyInside(t1<0, t2>1)

		if (dRoot1 >= 0 && dRoot1 <= 1)
		{
			// root 1 is the intersection, and it's closer than root 2
			// (since root 1 uses -b - discriminant)
			// Impale, Poke
			return true;
		}

		// here root 1 didn't intersect so we are either started
		// inside the sphere or completely past it
		if (dRoot2 >= 0 && dRoot2 <= 1)
		{
			// ExitWound
			return true;
		}

		if (dRoot1 < 0 && dRoot2 > 1)
		{
			// CompletelyInside
			return true;
		}

		// no intn: FallShort, Past, CompletelyInside
		return false;
	}
}

bool IsEqual(double first, double second) {
	bool equality = false;

	if (abs(first - second) < std::numeric_limits<double>::epsilon())	{
		equality = true;
	}

	return equality;
}

ProjectionResult Line::Project(glm::dvec2& pointToProject,
	glm::dvec2& intersectionPoint,
	double& proportion) {
	ProjectionResult result = ProjectionResult::ePR_WITHINLINE;

	double U = 0.0F;
	double LineMag = Magnitude(mPoint1, mPoint2);

	glm::dvec2 pointStartDiff;
	glm::dvec2 EndStartDiff;

	if (IsEqual(LineMag, 0.0F))	{
		U = 0.0F;
	}
	else {
		pointStartDiff = pointToProject - mPoint1;
		EndStartDiff = mPoint2 - mPoint1;

		U = (pointStartDiff.x * EndStartDiff.x +
			pointStartDiff.y * EndStartDiff.y) /
			(LineMag * LineMag);
	}

	if (U <= 0.0F)	{
		result = ProjectionResult::ePR_OUTSIDE_LINE_PRIOR_START;
	}
	else if (U > 1.0F)	{
		result = ProjectionResult::ePR_OUTSIDE_LINE_AFTER_END;
	}
	else	{
		intersectionPoint.x = (mPoint1.x + U * EndStartDiff.x);
		intersectionPoint.y = (mPoint1.y + U * EndStartDiff.y);
	}

	proportion = U;

	return result;
}

bool Line::Intersect(const Line& otherLine) {
	double d;
	double ra, rb, x, y;
	double ax1 = mPoint1.x;
	double ay1 = mPoint1.y;
	double ax2 = mPoint2.x;
	double ay2 = mPoint2.y;
	double bx1 = otherLine.mPoint1.x;
	double by1 = otherLine.mPoint1.y;
	double bx2 = otherLine.mPoint2.x;
	double by2 = otherLine.mPoint2.y;

	d = ((ax2 - ax1)*(by1 - by2) - (ay2 - ay1)*(bx1 - bx2));

	// lines are not parallel
	if (d)	{			
		ra = ((bx1 - ax1)*(by1 - by2) - (by1 - ay1)*(bx1 - bx2)) / d;
		rb = ((ax2 - ax1)*(by1 - ay1) - (ay2 - ay1)*(bx1 - ax1)) / d;

		x = ax1 + (ra)* (ax2 - ax1);
		y = ay1 + (ra)* (ay2 - ay1);
		return (ra >= 0.0 && ra <= 1.0 && rb >= 0.0 && rb <= 1.0);
	}

	// lines are parallel, not co-linear
	if (((bx1 - ax1)*(by1 - by2) - (by1 - ay1)*(bx1 - bx2))
		|| 
		((ax2 - ax1)*(by1 - ay1) - (ay2 - ay1)*(bx1 - ax1)))
		return false;

	if (ax1 > ax2)	{
		std::swap(ax1, ax2);
	}

	if (bx1 > bx2)	{
		std::swap(bx1, bx2);
	}

	if (ax1 > bx2)	{
		return false;
	}

	if (ax2 < bx1)	{
		return false;
	}

	// there is overlap
	if (ax1 == bx2)	{
		return true;		
	}

	if (ax2 == bx1)	{
		return true;
	}

	// colinear with overlap on an interval, not just a single point
	return true;			
}

IntersectionResult Line::Intersect(const Line& otherLine, glm::dvec2& intersection) {
	IntersectionResult result = IntersectionResult::eIR_NOT_INTERSECT;

	glm::dvec2 myp2minusp1 = mPoint2 - mPoint1;
	glm::dvec2 otherp2minusp1 = otherLine.mPoint2 - otherLine.mPoint1;
	glm::dvec2 myp1minusotherp1 = mPoint1 - otherLine.mPoint1;

	double denom =
		(otherp2minusp1.y * myp2minusp1.x) -
		(otherp2minusp1.x * myp2minusp1.y);

	double nume_a =
		(otherp2minusp1.x * myp1minusotherp1.y) -
		(otherp2minusp1.y * myp1minusotherp1.x);

	double nume_b =
		(myp2minusp1.x * myp1minusotherp1.y) -
		(myp2minusp1.y * myp1minusotherp1.x);

	if (true == IsEqual(denom, 0.0F)) {
		if ((true == IsEqual(nume_a, 0.0F))
			&&
			(true == IsEqual(nume_b, 0.0F))) {
			result = IntersectionResult::eIR_COINCIDENT;
		}
		else {
			result = IntersectionResult::eIR_PARALLEL;
		}
	}
	else {
		double ua = nume_a / denom;
		double ub = nume_b / denom;

		if ((ua >= 0.0F) && (ua <= 1.0F) && (ub >= 0.0F) && (ub <= 1.0F)) {
			// Get the intersection point.
			intersection.x = (mPoint1.x + ua * (mPoint2.x - mPoint1.x));
			intersection.y = (mPoint1.y + ua * (mPoint2.y - mPoint1.y));

			result = IntersectionResult::eIR_INTERSECT;
		}
	}

	return result;
}