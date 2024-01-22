#pragma once
#include "../Vec2.hpp"

class Rectangle
{
private:
	Vec2 m_topLeft;
	
	float m_width;
	float m_height;

public:
	Rectangle(const Vec2 a_topleft, const float a_width, const float a_height) : m_topLeft(a_topleft), m_width(a_width), m_height(a_height) {};
	
public:
	static Rectangle FromMiddle(const Vec2 a_middle, const float a_width, const float a_height)
	{
		return Rectangle(a_middle + Vec2(-a_width, a_height)/2, a_width, a_height);
	}

	static Rectangle FromBottemRight(const Vec2 a_bottemRight, const float a_width, const float a_height)
	{
		return Rectangle(a_bottemRight + Vec2(-a_width, a_height), a_width, a_height);
	}

	static Rectangle FromTopRight(const Vec2 a_topRight, const float a_width, const float a_height)
	{
		return Rectangle(a_topRight + Vec2(-a_width, 0), a_width, a_height);
	}

	static Rectangle FromBottemLeft(const Vec2 a_bottemLeft, const float a_width, const float a_height)
	{
		return Rectangle(a_bottemLeft + Vec2(0, a_height), a_width, a_height);
	}

	Vec2 Middle() const { return m_topLeft + Vec2(m_width, -m_height)/2.f; };
	Vec2 TopLeft() const { return m_topLeft; }
	Vec2 TopRight() const { return m_topLeft + Vec2(m_width, 0); };
	Vec2 BottemLeft() const { return m_topLeft + Vec2(0, -m_height); };
	Vec2 BottemRight() const { return m_topLeft + Vec2(m_width, -m_height); };

	float Width() const { return m_width; }
	float Height() const { return m_height; }

	bool IsInside(const Vec2 a_point) const
	{
		if (!couldBeInside(a_point)) return false;

		if (a_point.x < m_topLeft.x || a_point.y > m_topLeft.y) return false;
		
		const Vec2 bottemRight = BottemRight();

		if (a_point.x > bottemRight.x || a_point.y < bottemRight.y) return false;

		return true;
	};

private:
	bool couldBeInside(const Vec2 a_point) const
	{
		const Vec2 middle = Middle();
		const Vec2 maxRange = m_topLeft - middle;
		const Vec2 diffrence = a_point - middle;

		return maxRange.LengthSquared() > diffrence.LengthSquared();
	};
};

