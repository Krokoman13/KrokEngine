#pragma once

#include <vector>
#include "Mouse.hpp"
#include "Keyboard.hpp"
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
	static bool mouseButtons[Mouse::ButtonCount];
	static bool mouseButtonsUp[Mouse::ButtonCount];
	static bool mouseButtonsDown[Mouse::ButtonCount];

	static bool key[Keyboard::KeyCount];
	static bool keyDown[Keyboard::KeyCount];
	static bool keyUp[Keyboard::KeyCount];
};

