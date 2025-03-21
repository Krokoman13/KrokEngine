#pragma once
#include "Shape.hpp"

class Rectangle : public Shape
{
private:
	float m_width;
	float m_height;

public:
	Rectangle(const float a_width, const float a_height, const Vec2 a_middle = Vec2(0.f, 0.f)) : m_width(a_width), m_height(a_height) { SetMiddle(a_middle); };
	
public:
	static Rectangle FromTopLeft(const Vec2 a_topLeft, const float a_width, const float a_height)
	{
		return Rectangle(a_width, a_height, a_topLeft + Vec2(a_width, -a_height) / 2.f);
	}

	static Rectangle FromTopRight(const Vec2 a_topRight, const float a_width, const float a_height)
	{
		return Rectangle(a_width, a_height, a_topRight + Vec2(-a_width, -a_height) / 2.f);
	}

	static Rectangle FromBottemLeft(const Vec2 a_bottemLeft, const float a_width, const float a_height)
	{
		return Rectangle(a_width, a_height, a_bottemLeft + Vec2(a_width, a_height) / 2.f);
	}

	static Rectangle FromBottemRight(const Vec2 a_bottemRight, const float a_width, const float a_height)
	{
		return Rectangle(a_width, a_height, a_bottemRight + Vec2(-a_width, a_height) / 2.f);
	}

	Vec2 TopLeft() const { return GetMiddle() + Vec2(-m_width,  m_height) / 2.f; };
	Vec2 TopRight() const { return GetMiddle() + Vec2( m_width,  m_height) / 2.f; };
	Vec2 BottemLeft() const { return GetMiddle() + Vec2(-m_width, -m_height) / 2.f; };
	Vec2 BottemRight() const { return GetMiddle() + Vec2( m_width, -m_height) / 2.f; };

	float Width() const { return m_width; }
	float Height() const { return m_height; }

	bool IsInside(const Vec2 a_point, const Matrix3& a_identity) const override
	{
		const Vec2 scale = a_identity.GetScale();
		return Rectangle(m_width * scale.x, m_height * scale.y, GetMiddle() + a_identity.GetPos()).isInside(a_point);
	};

private:
	bool isInside(const Vec2 a_point) const
	{
		const Vec2 middle = GetMiddle();
		const Vec2 diffrence = a_point - middle;
		const Vec2 maxRange = Vec2(m_width / 2.f, m_height / 2.f) ;

		if (maxRange.LengthSquared() < diffrence.LengthSquared()) return false;
		const Vec2 topleft = TopLeft();

		if (a_point.x < topleft.x || a_point.y > topleft.y) return false;
		const Vec2 bottemRight = BottemRight();

		if (a_point.x > bottemRight.x || a_point.y < bottemRight.y) return false;

		return true;
	}
};

