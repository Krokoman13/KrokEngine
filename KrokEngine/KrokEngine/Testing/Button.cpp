#include "Button.hpp"

Button::Button(const int a_spriteAID, const int a_spriteBID, const int a_layer, const Rectangle a_rectangle)
{
	m_spriteA = AddComponent<Sprite>(a_spriteAID);
	m_spriteA->SetRenderLayer(a_layer);
	m_spriteA->SetLocalScale(Vec2(a_rectangle.Width(), a_rectangle.Height()));

	m_spriteB = AddComponent<Sprite>(a_spriteBID);
	m_spriteB->SetRenderLayer(a_layer);
	m_spriteB->SetLocalScale(Vec2(a_rectangle.Width(), a_rectangle.Height()));

	m_cliclable = AddComponent<Clickable>(a_rectangle, a_layer);
}

void Button::update()
{
	bool isHovering = m_cliclable->IsHovering();

	if (m_cliclable->IsPressed(Mouse::Button::Left)) isHovering = !isHovering;
	//std::cout << isHovering << std::endl;
	m_spriteA->SetActive(!isHovering);
	m_spriteB->SetActive(isHovering);
}
