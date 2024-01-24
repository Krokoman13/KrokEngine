#pragma once
#include "../Engine/KrokEngine.hpp"

class ButtonObject : public GameObject
{
private:
	Sprite* m_spriteA = nullptr;
	Sprite* m_spriteB = nullptr;
	ButtonComponent* m_buttonComp = nullptr;

public:
	ButtonObject(const int a_spriteAID, const int a_spriteBID, const Rectangle a_rectangle, const int a_layer = 10);
	void SetFunction(const std::function<void()> a_function) { m_buttonComp->SetFunction(a_function); };
	void SetMouseButton(const Mouse::Button a_mouseButton) { m_buttonComp->SetMouseButton(a_mouseButton); }

protected:
	void update() override;
};

