#include "Input.hpp"

template <typename E>
constexpr auto to_underlying(E e) noexcept {
	return static_cast<std::underlying_type_t<E>>(e);
}

bool Input::focus = true;

bool Input::mouseInScreen = true;
Vec2 Input::mousePosition = Vec2(0.0f, 0.0f);
Vec2 Input::previousMousePosition = Vec2(0.0f, 0.0f);
bool Input::mouseButtons[Mouse::ButtonCount] = { false };
bool Input::mouseButtonsUp[Mouse::ButtonCount] = { false };
bool Input::mouseButtonsDown[Mouse::ButtonCount] = { false };

bool Input::key[Keyboard::KeyCount] = { false };
bool Input::keyDown[Keyboard::KeyCount] = { false };
bool Input::keyUp[Keyboard::KeyCount] = { false };

bool Input::IsPressed(Keyboard::Key pKey)
{
	return key[static_cast<unsigned int>(pKey)];
}

bool Input::IsPressed(Mouse::Button pMouseButton)
{
	return mouseButtons[static_cast<unsigned int>(pMouseButton)];
}

bool Input::WentDown(Keyboard::Key pKey)
{
	return keyDown[static_cast<unsigned int>(pKey)];
}

bool Input::WentDown(Mouse::Button pMouseButton)
{
	return mouseButtonsDown[static_cast<unsigned int>(pMouseButton)];
}

bool Input::WentUp(Keyboard::Key pKey)
{
	return keyUp[static_cast<unsigned int>(pKey)];
}

bool Input::WentUp(Mouse::Button pMouseButton)
{
	return mouseButtonsUp[static_cast<unsigned int>(pMouseButton)];
}
