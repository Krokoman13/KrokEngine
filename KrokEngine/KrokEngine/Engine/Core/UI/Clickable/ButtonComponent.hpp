#pragma once
#include "Clickable.hpp"
#include <functional>

class ButtonComponent : public Clickable
{
private:
	Mouse::Button m_mouseButton = Mouse::Button::Left;
	std::function<void()> m_function;

public:
	using Clickable::Clickable;

public:
	void SetFunction(const std::function<void()> a_function) { m_function = a_function; };
	void SetMouseButton(const Mouse::Button a_mouseButton) { m_mouseButton = a_mouseButton; }

private:
	virtual void onPressed(const Mouse::Button a_mouseButton) override { if (a_mouseButton == m_mouseButton && m_function) m_function(); };
};