#pragma once
#include "Monster.hpp"

#include "../Components/SpriteFlipper.hpp"

class Bat : public GameObject, public Monster
{
public:
	Bat(const Vec2 a_pos)
	{
		float size = 16.f;

		m_animSprite = AddComponent<AnimationSprite>(RS__FLY_ANIM_SPRITESHEET_PNG, 4, 1, false);
		m_animSprite->SetDisplayMode(DisplayMode::BottomCenter);
		Animation defaultAnimation = Animation(0, 3, 0.1f,
			[this]() {
				this->TryToAttack();
			});
		m_animSprite->AddAnimation(defaultAnimation, "DEFAULT");
		m_animSprite->SetRenderLayer(500);

		m_rigBody = AddComponent<RigidBody>();

		m_follBehaviour = AddComponent<FollowBehaviour>();
		m_follBehaviour->speed = 15.f;
		m_follBehaviour->minDistance = 16.f;

		m_health = AddComponent<Health>();
		m_health->SetHealth(1);
		Sprite* sprite = m_animSprite;
		m_health->SetOnInvicibleEnter([sprite]() { sprite->diffuseColor = Color::Red(); });
		m_health->SetOnInvicibleExit([sprite]() { sprite->diffuseColor = Color::White(); });

		AddComponent<TriggerColliderComponent>(new CircleCollider(8, Vec2(0, 8)));
		AddComponent<SpriteFlipper>();
	}
};