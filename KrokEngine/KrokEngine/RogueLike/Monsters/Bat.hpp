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
		m_animSprite->AddAnimation(Animation(0, 3, 0.1f), "DEFAULT");
		m_animSprite->SetRenderLayer(100);

		m_rigBody = AddComponent<RigidBody>();

		m_follBehaviour = AddComponent<FollowBehaviour>();
		m_follBehaviour->speed = 15.f;

		health = AddComponent<Health>();
		health->SetHealth(1);

		AddComponent<SpriteFlipper>();
	}
};