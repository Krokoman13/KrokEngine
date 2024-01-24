#pragma once
#include "../Vec2.hpp"
#include "../Matrix3.hpp"

class Shape
{
private:
	Vec2 m_middle;

public:
	Vec2 GetMiddle() const { return m_middle; };
	void SetMiddle(const Vec2 a_middle) { m_middle = a_middle; };

	virtual bool IsInside(const Vec2 a_point, const Matrix3& a_identity) const = 0;
};

