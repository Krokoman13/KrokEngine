#include "Input.hpp"

bool Input::focus = true;

bool Input::mouseInScreen = true;
Vec2 Input::mousePosition = Vec2(0.0f, 0.0f);
bool Input::mouseButtons[sf::Mouse::Button::ButtonCount] = { false };

bool Input::key[sf::Keyboard::Key::KeyCount] = { false };

bool Input::IsPressed(sf::Keyboard::Key pKey)
{
	return key[pKey];
}

bool Input::IsPressed(sf::Mouse::Button pMouseButton)
{
	return mouseButtons[pMouseButton];
}