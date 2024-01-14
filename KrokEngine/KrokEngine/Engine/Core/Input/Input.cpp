#include "Input.hpp"

bool Input::focus = true;

bool Input::mouseInScreen = true;
Vec2 Input::mousePosition = Vec2(0.0f, 0.0f);
Vec2 Input::previousMousePosition = Vec2(0.0f, 0.0f);
bool Input::mouseButtons[Mouse::Button::ButtonCount] = { false };
bool Input::mouseButtonsUp[Mouse::Button::ButtonCount] = { false };
bool Input::mouseButtonsDown[Mouse::Button::ButtonCount] = { false };

bool Input::key[Keyboard::Key::KeyCount] = { false };
bool Input::keyDown[Keyboard::Key::KeyCount] = { false };
bool Input::keyUp[Keyboard::Key::KeyCount] = { false };

bool Input::IsPressed(Keyboard::Key pKey)
{
	return key[pKey];
}

bool Input::IsPressed(Mouse::Button pMouseButton)
{
	return mouseButtons[pMouseButton];
}

bool Input::WentDown(Keyboard::Key pKey)
{
	return keyDown[pKey];
}

bool Input::WentDown(Mouse::Button pMouseButton)
{
	return mouseButtonsDown[pMouseButton];
}

bool Input::WentUp(Keyboard::Key pKey)
{
	return keyUp[pKey];
}

bool Input::WentUp(Mouse::Button pMouseButton)
{
	return mouseButtonsUp[pMouseButton];
}
