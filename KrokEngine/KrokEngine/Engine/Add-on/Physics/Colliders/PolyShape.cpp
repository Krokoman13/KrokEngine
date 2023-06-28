#include "PolyShape.hpp"

PolyShape::PolyShape()
{
}

PolyShape::PolyShape(const std::vector<Vec2>& pPoints)
{
	_points = pPoints;
}

PolyShape PolyShape::Rectangle(const Vec2 pUpLeft, const Vec2 pDownRight)
{
	const Vec2 diffrence = pDownRight - pUpLeft;

	PolyShape outp;
	outp._points.push_back(pUpLeft);
	outp._points.push_back(pUpLeft + Vec2(diffrence.x, 0.0f));
	outp._points.push_back(pDownRight);
	outp._points.push_back(pDownRight - Vec2(diffrence.x, 0.0f));
	return outp;
}

PolyShape PolyShape::Rectangle(const Vec2 pUpLeft, const float pWidth, const float pHeight)
{
	return Rectangle(pUpLeft, pUpLeft + Vec2(pWidth, pHeight));
}

PolyShape& PolyShape::Rotate(const float pRadians)
{
	rotateAround(pRadians, CalculateMidPoint());
	return *this;
}

PolyShape& PolyShape::Translate(const Vec2 pTranslation)
{
	for (Vec2& point : _points)
	{
		point += pTranslation;
	}

	return *this;
}

PolyShape& PolyShape::Invert()
{
	std::vector<Vec2> copy = _points;
	_points.clear();

	while (!copy.empty())
	{
		_points.push_back(copy.back());
		copy.pop_back();
	}

	return *this;
}

PolyShape PolyShape::SymetricShape(const unsigned int pCorners, const float pDiameter)
{
	float degStep = 365.0f / pCorners;
	PolyShape outp;

	for (unsigned int i = 0; i < pCorners; i++)
	{
		Vec2 point(0, pDiameter);
		point.RotateDegrees(degStep * i);
		outp._points.push_back(point);
	}

	return outp;
}

Vec2 PolyShape::CalculateMidPoint()
{
	Vec2 midpoint;

	for (const Vec2& point : _points)
	{
		midpoint += point;
	}

	return midpoint / (float)_points.size();
}

void PolyShape::rotateAround(const float pRadians, const Vec2 pMidPoint)
{
	for (Vec2& point : _points)
	{
		point.RotateAroundRadians(pRadians, pMidPoint);
	}
}
