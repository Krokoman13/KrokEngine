#pragma once
#include "../Engine/Add-on/Physics.hpp"
#include "../Engine/KrokEngine.hpp"

#include "Components/GridLayerer.hpp"
#include "Components/Burnable.hpp"

class Chest : public GameObject
{
private:
	AnimationSprite* m_animSprite;

public:
	Chest(Vec2 a_pos) : GameObject(a_pos, "Pillar")
	{
		m_animSprite = AddComponent<AnimationSprite>(RS__CHEST_SPRITESHEET_PNG, 8, 1);

		Animation shineingAnimation = Animation(0, 7, 0.1f);
		shineingAnimation.frames[0].SetDuration(10.f);
		m_animSprite->AddAnimation(shineingAnimation, "SHINEING");
		m_animSprite->SetDisplayMode(DisplayMode::BottomCenter);
		//m_animSprite->SetCurrentFrame(0);

		float xsize = 16;
		float ysize = 10;
		Vec2 offset = -Vec2(xsize / 2.f, ysize);
		ColliderComponent* colliderComp = AddComponent<ColliderComponent>(PolyShape::Rectangle(offset, xsize, ysize));
		colliderComp->bounciness = 0;

		AddComponent<GridLayerer>();
		AddComponent<Burnable>();
	}
};

