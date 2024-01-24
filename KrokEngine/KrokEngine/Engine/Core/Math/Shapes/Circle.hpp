#pragma once
#include "Shape.hpp"

class Circle : public Shape
{
private:
	float m_radius;

public:
	Circle(const float a_diameter) : m_radius(a_diameter / 2.f) {};

public:
	bool IsInside(const Vec2 a_point, const Matrix3& a_identity) const override
	{
		const Vec2 diffrence = a_point + a_identity.GetPos() - GetMiddle();;

		const Vec2 scale = a_identity.GetScale();
		const Vec2 maxRange = Vec2(m_radius * scale.x, m_radius * scale.y);

		return maxRange.LengthSquared() < diffrence.LengthSquared();
	}
};
