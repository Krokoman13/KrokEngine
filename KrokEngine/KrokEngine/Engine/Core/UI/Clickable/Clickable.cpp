#include "Clickable.hpp"

void Clickable::OnClick(Mouse::Button a_mouseButton)
{
	m_isPressed[(int)a_mouseButton] = true;

	onClick(a_mouseButton);
}

void Clickable::OnRelease(Mouse::Button a_mouseButton)
{
	m_isPressed[(int)a_mouseButton] = false;

	onRelease(a_mouseButton);
}

bool Clickable::IsPressed(Mouse::Button a_mouseButton)
{
	auto it = m_isPressed.find((int)a_mouseButton);
	if (it == m_isPressed.end()) return false;
	return it->second;
}

void Clickable::changeHovering(const bool a_isOver)
{
	Hoverable::changeHovering(a_isOver);
	if (a_isOver) return;

	for (auto& pair : m_isPressed) pair.second = false;
}

void Clickable::onClick(Mouse::Button a_mouseButton)
{
}

void Clickable::onRelease(Mouse::Button a_mouseButton)
{
}
