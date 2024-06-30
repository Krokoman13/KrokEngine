#include "Goblin.hpp"

#include "../Components/SpriteFlipper.hpp"
#include "../Components/GridLayerer.hpp"


Goblin::Goblin(const Vec2 a_pos) : GameObject(a_pos, "Goblin")
{
	const float size = 16.f;
	m_loadDuration = m_loadTime;

	m_animSprite = AddComponent<AnimationSprite>(RS__GOBLIN_SPRITESHEET_PNG, 6, 2, false);
	m_animSprite->SetDisplayMode(DisplayMode::BottomCenter);
	m_animSprite->AddAnimation(Animation(0, 5, 0.1f, [this]()
		{
			this->TryToAttack();
		}), "IDLE");
	m_animSprite->AddAnimation(Animation(6, 11, 0.1f), "RIGHT");
	m_animSprite->SetRenderLayer(100);

	m_rigBody = AddComponent<RigidBody>();
	float xsize = 13;
	float ysize = 6;
	Vec2 offset = -Vec2(xsize / 2.f, ysize);
	m_rigBody->Add(PolyShape::Rectangle(offset, xsize, ysize));
	m_rigBody->bounciness = 0;

	m_follBehaviour = AddComponent<FollowBehaviour>();
	m_follBehaviour->minDistance = 5 * (size * 4);

	m_health = AddComponent<Health>();
	m_health->SetHealth(4);
	Sprite* sprite = m_animSprite;
	m_health->SetOnInvicibleEnter([sprite]() { sprite->diffuseColor = Color::Red(); });
	m_health->SetOnInvicibleExit([sprite]() { sprite->diffuseColor = Color::White(); });

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

void Goblin::attack()
{
	m_loadDuration += 1;
	if (m_loadDuration < m_loadTime) return;
	m_loadDuration = 0;

	Bomb* bomb = new Bomb(m_follBehaviour->target->GetGlobalPosition());
	GetScene()->AddChild(bomb);
	bomb->SetGlobalPosition(GetGlobalPosition());
}