#pragma once

#include <vector>
#include "../Math/Vec2.hpp"

class Input
{
public:
	static bool IsPressed(Keyboard::Key pKey);
	static bool IsPressed(Mouse::Button pMouseButton);

	static bool WentDown(Keyboard::Key pKey);
	static bool WentDown(Mouse::Button pMouseButton);

	static bool WentUp(Keyboard::Key pKey);
	static bool WentUp(Mouse::Button pMouseButton);
	
public:
	static bool focus;

	static bool mouseInScreen;
	static Vec2 mousePosition;
	static Vec2 previousMousePosition;
	static bool mouseButtons[Mouse::Button::ButtonCount];
	static bool mouseButtonsUp[Mouse::Button::ButtonCount];
	static bool mouseButtonsDown[Mouse::Button::ButtonCount];

	static bool key[Keyboard::Key::KeyCount];
	static bool keyDown[Keyboard::Key::KeyCount];
	static bool keyUp[Keyboard::Key::KeyCount];
};

