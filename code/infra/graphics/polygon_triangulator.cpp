#include "polygon_triangulator.h"

const int32_t cIntegralTwo = 2;
const float cHalfOne = 0.5F;
const float EPSILON = 0.0000000001F;

float PolygonTriangulator::GetArea(const std::vector<glm::vec2>& contour) {
	int32_t n = static_cast<int32_t>(contour.size());
		
	float A = 0.0F;

	int32_t p = n - 1;
	int32_t q = 0;

	for (; q < n; p = q++)	{
		if ((p < static_cast<int32_t>(contour.size())) && (q < static_cast<int32_t>(contour.size()))) {
			glm::vec2 pointP = contour[p];
			glm::vec2 pointQ = contour[q];

			A += (pointP.x * pointQ.y - pointQ.x * pointP.y);
		}
	}

	return A * cHalfOne;
}

bool PolygonTriangulator::IsInsideTriangle(const glm::vec2& A,
												const glm::vec2& B,
												const glm::vec2& C,
												const glm::vec2& P) {
	float ax, ay, bx, by, cx, cy, apx, apy, bpx, bpy, cpx, cpy;
	float cCROSSap, bCROSScp, aCROSSbp;

	float Ax = A.x;
	float Ay = A.y;
	float Bx = B.x;
	float By = B.y;
	float Cx = C.x;
	float Cy = C.y;
	float Px = P.x;
	float Py = P.y;

	ax = Cx - Bx;
	ay = Cy - By;
	bx = Ax - Cx;
	by = Ay - Cy;
	cx = Bx - Ax;
	cy = By - Ay;
	apx = Px - Ax;
	apy = Py - Ay;
	bpx = Px - Bx;
	bpy = Py - By;
	cpx = Px - Cx;
	cpy = Py - Cy;

	aCROSSbp = ax*bpy - ay*bpx;
	cCROSSap = cx*apy - cy*apx;
	bCROSScp = bx*cpy - by*cpx;

	return ((aCROSSbp >= 0.0f) && (bCROSScp >= 0.0f) && (cCROSSap >= 0.0f));
}

bool PolygonTriangulator::Snip(const std::vector<glm::vec2>& contour,
	int32_t u,
	int32_t v,
	int32_t w,
	int32_t n,
	int32_t* V)	{
	int32_t p;
	float Ax;
	float Ay;
	float Bx;
	float By;
	float Cx;
	float Cy;

	glm::vec2 pointA;
	pointA = contour[V[u]];

	glm::vec2 pointB;
	pointB = contour[V[v]];

	glm::vec2 pointC;
	pointC = contour[V[w]];

	glm::vec2 pointP;

	Ax = pointA.x;
	Ay = pointA.y;

	Bx = pointB.x;
	By = pointB.y;

	Cx = pointC.x;
	Cy = pointC.y;

	if (EPSILON > (((Bx - Ax)*(Cy - Ay)) - ((By - Ay)*(Cx - Ax))))
		return false;

	for (p = 0; p < n; p++)	{
		if (false == ((p == u)
			||
			(p == v)
			||
			(p == w)))	{
			pointP = contour[V[p]];

			if (IsInsideTriangle(pointA, pointB, pointC, pointP)) {
				return false;
			}
		}
	}

	return true;
}

bool PolygonTriangulator::Triangulate(const std::vector<glm::vec2>& polygon, std::vector<glm::vec2>& triangulatedTriangles)	{
	int32_t n = static_cast<int32_t>(polygon.size());
	glm::vec2 firstPoint;
	glm::vec2 lastPoint;
	firstPoint = polygon[0];
	lastPoint = polygon[n - 1];

	if (firstPoint == lastPoint) {
		n = n - 1;
	}

	const int32_t cTrianglePointCount = 3U;
	const int32_t cMaxNoOfPoints = 2048U;

	if ((n < cTrianglePointCount)
		||
		(n > cMaxNoOfPoints)) {
		// draw incoming polygon directly
		return false;
	}

	int32_t V[cMaxNoOfPoints];

	// check counter clockwise ordering
	if (0.0F < GetArea(polygon)) {
		for (int32_t v = 0; v < n; v++)	{
			V[v] = v;
		}
	}
	else {
		for (int32_t v = 0; v < n; v++)	{
			V[v] = (n - 1) - v;
		}
	}

	int32_t nv = n;

	//  remove nv-2 Vertices, creating 1 triangle every time
	int32_t count = cIntegralTwo * nv;

	glm::vec2 pointA;
	glm::vec2 pointB;
	glm::vec2 pointC;

	triangulatedTriangles.clear();

	for (int32_t m = 0, v = nv - 1; nv > cIntegralTwo; ) {
		// if we loop, it is probably a non-simple polygon
		if (0 >= (count--)) {
			// bad polygon
			return false;
		}

		// three consecutive vertices in current polygon, <u,v,w>
		int32_t u = v;
		if (nv <= u) {
			u = 0;     // previous
		}

		v = u + 1;
		if (nv <= v) {
			v = 0;     // new v
		}

		int32_t w = v + 1;
		if (nv <= w) {
			w = 0;     // next
		}

		if (Snip(polygon, u, v, w, nv, &V[0])) {
			int32_t a, b, c, s, t;

			// true names of the vertices
			a = V[u];
			b = V[v];
			c = V[w];

			// output Triangle
			pointA = polygon[a];
			pointB = polygon[b];
			pointC = polygon[c];
				
			triangulatedTriangles.push_back(pointA);
			triangulatedTriangles.push_back(pointB);
			triangulatedTriangles.push_back(pointC);

			m++;

			// remove v from remaining polygon
			for (s = v, t = v + 1; t < nv; s++, t++) {
				V[s] = V[t];
			}

			nv--;

			// reset error detection counter
			count = cIntegralTwo*nv;
		}
	}

	return true;
}