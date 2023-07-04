#pragma once
#include "CircleCollider.hpp"

class PointCollider : public CircleCollider
{
public:
	PointCollider(Vec2 pOffset = Vec2(0.0f, 0.0f)) : CircleCollider(_pointRange, pOffset) {}

	virtual float GetRadius() const override { return _pointRange; }

private:
	const float _pointRange = 0.0f;
};

