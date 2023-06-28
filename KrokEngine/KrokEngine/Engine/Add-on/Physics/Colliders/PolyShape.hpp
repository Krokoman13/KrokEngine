#pragma once
#include <vector>
#include "../../../Core/Math/Vec2.hpp"

struct PolyShape
{
	PolyShape(const std::vector<Vec2>& pPoints);
	operator std::vector<Vec2> () const { return _points; }
	static PolyShape Rectangle(const Vec2 pUpLeft, const Vec2 pDownRight);
	static PolyShape Rectangle(const Vec2 pUpLeft, const float pWidth, const float pHeight);

	static PolyShape SymetricShape(const unsigned int pCorners, const float pDiameter);
	static PolyShape Triangle(const float pDiameter) { return (SymetricShape(3, pDiameter)); }

	PolyShape& Rotate(const float pRadians);
	PolyShape& Translate(const Vec2 pTranslation);
	PolyShape& Invert();
	Vec2 CalculateMidPoint();

private:
	std::vector<Vec2> _points;
	PolyShape();
	void rotateAround(const float pRadians, const Vec2 pMidPoint);
};