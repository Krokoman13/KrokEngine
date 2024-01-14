#pragma once
#include "Hoverable.hpp"

class Clickable : public Hoverable
{
public:
	Clickable(std::string name, std::string path, float x, float y);
	Clickable(std::string name, float x, float y);

	virtual void OnClick() = 0;

	Mouse::Button onClickButton = Mouse::Button::Left;
};

