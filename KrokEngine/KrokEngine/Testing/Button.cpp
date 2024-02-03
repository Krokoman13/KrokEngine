#include "Button.hpp"

ButtonObject::ButtonObject(const int a_spriteAID, const int a_spriteBID, const Rectangle a_rectangle, const int a_layer) : GameObject(a_rectangle.TopLeft(), "Button")
{
	m_spriteA = AddComponent<Sprite>(a_spriteAID);
	m_spriteA->SetRenderLayer(a_layer);
	m_spriteA->SetLocalScale(Vec2(a_rectangle.Width(), a_rectangle.Height()));

	m_spriteB = AddComponent<Sprite>(a_spriteBID);
	m_spriteB->SetRenderLayer(a_layer);
	m_spriteB->SetLocalScale(Vec2(a_rectangle.Width(), a_rectangle.Height()));

	m_buttonComp = AddComponent<ButtonComponent>(a_rectangle, a_layer);
}

void ButtonObject::update()
{
	bool isHovering = m_buttonComp->IsHovering();

	if (m_buttonComp->IsPressed(Mouse::Button::Left)) isHovering = !isHovering;
	m_spriteA->SetActive(!isHovering);
	m_spriteB->SetActive(isHovering);
}
