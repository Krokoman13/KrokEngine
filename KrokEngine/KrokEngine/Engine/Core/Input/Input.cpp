#include "Input.hpp"

bool Input::focus = true;

bool Input::mouseInScreen = true;
Vec2 Input::mousePosition = Vec2(0.0f, 0.0f);
Vec2 Input::previousMousePosition = Vec2(0.0f, 0.0f);
bool Input::mouseButtons[sf::Mouse::Button::ButtonCount] = { false };
bool Input::mouseButtonsUp[sf::Mouse::Button::ButtonCount] = { false };
bool Input::mouseButtonsDown[sf::Mouse::Button::ButtonCount] = { false };

bool Input::key[sf::Keyboard::Key::KeyCount] = { false };
bool Input::keyDown[sf::Keyboard::Key::KeyCount] = { false };
bool Input::keyUp[sf::Keyboard::Key::KeyCount] = { false };

bool Input::IsPressed(sf::Keyboard::Key pKey)
{
	return key[pKey];
}

bool Input::IsPressed(sf::Mouse::Button pMouseButton)
{
	return mouseButtons[pMouseButton];
}

bool Input::WentDown(sf::Keyboard::Key pKey)
{
	return keyDown[pKey];
}

bool Input::WentDown(sf::Mouse::Button pMouseButton)
{
	return mouseButtonsDown[pMouseButton];
}

bool Input::WentUp(sf::Keyboard::Key pKey)
{
	return keyUp[pKey];
}

bool Input::WentUp(sf::Mouse::Button pMouseButton)
{
	return mouseButtonsUp[pMouseButton];
}
