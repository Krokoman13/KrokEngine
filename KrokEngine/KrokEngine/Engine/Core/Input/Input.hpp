#pragma once

#include <vector>
#include <unordered_map>

#include "Mouse.hpp"
#include "Keyboard.hpp"
#include "../Math/Vec2.hpp"

class EventHandeler;

class Input
{
public:
	static inline bool MouseInScreen() { return m_mouseInScreen; }
	static inline bool MouseMoved() { return m_mouseMoved; }

	static inline Vec2 MousePos() { return m_mousePosition; }
	static inline Vec2 PrevMousePos() { return m_previousMousePosition; }

	static bool IsPressed(const Keyboard::Key a_key);
	static bool IsPressed(const Mouse::Button a_mouseButton);

	static bool WentDown(const Keyboard::Key a_key);
	static bool WentDown(const Mouse::Button a_mouseButton);

	static bool WentUp(const Keyboard::Key a_key);
	static bool WentUp(const Mouse::Button a_mouseButton);

private:
	static bool read(const std::unordered_map<int, bool>& a_map, const int key);

	friend class EventHandeler;

	static std::unordered_map<int, bool> m_keyWentDown;
	static std::unordered_map<int, bool> m_keyWentUp;
	static std::unordered_map<int, bool> m_keyIsPressed;

	static std::unordered_map<int, bool> m_mouseWentDown;
	static std::unordered_map<int, bool> m_mouseWentUp;
	static std::unordered_map<int, bool> m_mouseIsPressed;

	static bool m_mouseInScreen;
	static bool m_mouseMoved;

	static Vec2 m_mousePosition;
	static Vec2 m_previousMousePosition;
};

