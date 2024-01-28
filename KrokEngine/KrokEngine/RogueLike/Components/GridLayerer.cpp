#include "GridLayerer.hpp"

void GridLayerer::OnEnable()
{
	if (!m_mySprite && !m_gameObject->TryGetComponent<Sprite>(m_mySprite))
	{
		std::cout << "WARNING: Spriteflipper is not attached to a gameobject that contains a sprite" << std::endl;
		SetActive(false);
		return;
	}

	SetLayer();
}

void GridLayerer::Update()
{
	SetLayer();
}

void GridLayerer::SetLayer()
{
	const Vec2 pos = m_gameObject->GetGlobalPosition();
	m_mySprite->SetRenderLayer(unsigned int(pos.y / m_ySize));
}
