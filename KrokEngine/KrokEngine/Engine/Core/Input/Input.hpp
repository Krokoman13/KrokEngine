#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Math/Vec2.hpp"

class Input
{
public:
	static bool IsPressed(sf::Keyboard::Key pKey);
	static bool IsPressed(sf::Mouse::Button pMouseButton);
	
public:
	static bool focus;

	static bool mouseInScreen;
	static Vec2 mousePosition;
	static bool mouseButtons[sf::Mouse::Button::ButtonCount];

	static bool key[sf::Keyboard::Key::KeyCount];
};

