#include "Goblin.hpp"

#include "../Components/SpriteFlipper.hpp"
#include "../Components/GridLayerer.hpp"

Goblin::Goblin(const Vec2 a_pos) : GameObject(a_pos, "Goblin")
{
	const float size = 16.f;

	m_animSprite = AddComponent<AnimationSprite>(RS__GOBLIN_SPRITESHEET_PNG, 6, 2, false);
	m_animSprite->SetDisplayMode(DisplayMode::BottomCenter);
	m_animSprite->AddAnimation(Animation(0, 5, 0.1f), "IDLE");
	m_animSprite->AddAnimation(Animation(6, 11, 0.1f), "RIGHT");
	m_animSprite->SetRenderLayer(100);

	m_rigBody = AddComponent<RigidBody>();
	float xsize = 13;
	float ysize = 6;
	Vec2 offset = -Vec2(xsize / 2.f, ysize);
	m_rigBody->Add(PolyShape::Rectangle(offset, xsize, ysize));
	m_rigBody->bounciness = 0;

	m_follBehaviour = AddComponent<FollowBehaviour>();
	m_follBehaviour->minDistance = 5 * size;

	health = AddComponent<Health>();
	health->SetHealth(1);

	AddComponent<SpriteFlipper>();
	AddComponent<GridLayerer>();
}

void Goblin::update()
{
	if (m_rigBody->velocity.LengthSquared() < 0.1f)
	{
		m_animSprite->SetCurrentAnimation("IDLE");
		return;
	}
	m_animSprite->SetCurrentAnimation("RIGHT");
}
