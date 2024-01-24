#pragma once
#include "Hoverable/Hoverable.hpp"
#include <unordered_map>

#include "../../Input/Mouse.hpp"

class Clickable : public Hoverable
{
private:
	std::unordered_map<int, bool> m_isPressed;

public:
	using Hoverable::Hoverable;

	void OnClick(Mouse::Button a_mouseButton);
	void OnRelease(Mouse::Button a_mouseButton);

	bool IsPressed(Mouse::Button a_mouseButton);

protected:
	virtual void changeHovering(const bool a_isOver) override;

	virtual void onPressed(Mouse::Button a_mouseButton);
	virtual void onRelease(Mouse::Button a_mouseButton);
};

