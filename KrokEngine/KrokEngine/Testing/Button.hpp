#pragma once
#include "../Engine/KrokEngine.hpp"

class Button : public GameObject
{
private:
	Sprite* m_spriteA = nullptr;
	Sprite* m_spriteB = nullptr;
	Clickable* m_cliclable = nullptr;

public:
	Button(const int a_spriteAID, const int a_spriteBID, const int a_layer, const Rectangle a_rectangle);

protected:
	void update() override;
};

