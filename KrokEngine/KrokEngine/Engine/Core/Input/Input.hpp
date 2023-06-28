#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Math/Vec2.hpp"

class Input
{
public:
	static bool IsPressed(sf::Keyboard::Key pKey);
	static bool IsPressed(sf::Mouse::Button pMouseButton);

	static bool WentDown(sf::Keyboard::Key pKey);
	static bool WentDown(sf::Mouse::Button pMouseButton);

	static bool WentUp(sf::Keyboard::Key pKey);
	static bool WentUp(sf::Mouse::Button pMouseButton);
	
public:
	static bool focus;

	static bool mouseInScreen;
	static Vec2 mousePosition;
	static Vec2 previousMousePosition;
	static bool mouseButtons[sf::Mouse::Button::ButtonCount];
	static bool mouseButtonsUp[sf::Mouse::Button::ButtonCount];
	static bool mouseButtonsDown[sf::Mouse::Button::ButtonCount];

	static bool key[sf::Keyboard::Key::KeyCount];
	static bool keyDown[sf::Keyboard::Key::KeyCount];
	static bool keyUp[sf::Keyboard::Key::KeyCount];
};

