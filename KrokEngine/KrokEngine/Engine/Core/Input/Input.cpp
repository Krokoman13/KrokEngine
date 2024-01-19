#include "Input.hpp"

template <typename E>
constexpr auto to_underlying(E e) noexcept {
	return static_cast<std::underlying_type_t<E>>(e);
}

bool Input::m_mouseInScreen = true;
bool Input::m_mouseMoved = false;

Vec2 Input::m_mousePosition = Vec2(0.0f, 0.0f);
Vec2 Input::m_previousMousePosition = Vec2(0.0f, 0.0f);

std::unordered_map<int, bool> Input::m_keyWentDown;
std::unordered_map<int, bool> Input::m_keyWentUp;
std::unordered_map<int, bool> Input::m_keyIsPressed;

std::unordered_map<int, bool> Input::m_mouseWentDown;
std::unordered_map<int, bool> Input::m_mouseWentUp;
std::unordered_map<int, bool> Input::m_mouseIsPressed;

bool Input::IsPressed(const Keyboard::Key a_key)
{
	return read(m_keyIsPressed, (int)a_key);
}

bool Input::IsPressed(const Mouse::Button a_mouseButton)
{
	return read(m_mouseIsPressed, (int)a_mouseButton);
}

bool Input::WentDown(const Keyboard::Key a_key)
{
	return read(m_keyWentDown, (int)a_key);
}

bool Input::WentDown(const Mouse::Button a_mouseButton)
{
	return read(m_mouseWentDown, (int)a_mouseButton);
}

bool Input::WentUp(const Keyboard::Key a_key)
{
	return read(m_keyWentUp, (int)a_key);
}

bool Input::WentUp(const Mouse::Button a_mouseButton)
{
	return read(m_mouseWentUp, (int)a_mouseButton);
}

bool Input::read(const std::unordered_map<int, bool>& a_map, const int key)
{
	auto it = a_map.find(key);
	if (it == a_map.end()) return false;
	return it->second;
}
