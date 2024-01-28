#include "Hoverable.hpp"
#include "../../../Math/Matrix3.hpp"
#include "../../../../Essentials/GameObject.hpp"

Hoverable::~Hoverable()
{
}

void Hoverable::SetShape(const Circle a_cirlce)
{
	m_shape = std::make_unique<Circle>(a_cirlce);
}

void Hoverable::SetShape(const Rectangle a_rectangle)
{
	m_shape = std::make_unique<Rectangle>(a_rectangle);
}

bool Hoverable::IsInside(const Vec2 a_point) const
{
	Matrix3 global = GetGameObject()->MatrixInScreen();
	return m_shape->IsInside(a_point, global);
}

void Hoverable::SetHovering(const bool a_isOver)
{
	if (a_isOver == m_isOver) return;

	changeHovering(a_isOver);

	if (m_isOver) OnStartHovering();
	else OnStopHovering();
}

void Hoverable::OnStartHovering()
{
}

void Hoverable::OnStopHovering()
{
}

void Hoverable::changeHovering(const bool a_isOver)
{
	m_isOver = a_isOver;
}