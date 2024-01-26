#pragma once
#include "../Engine/Add-on/Physics.hpp"
#include "../Engine/KrokEngine.hpp"

class Pillar : public GameObject
{
private:
	AnimationSprite* m_animSprite;

public:
	Pillar(Vec2 a_pos) : GameObject(a_pos, "Pillar")
	{
		m_animSprite = AddComponent<AnimationSprite>(RS__CHEST_SPRITESHEET_PNG, 8, 1);
		m_animSprite->SetDisplayMode(DisplayMode::Center);
		m_animSprite->SetCurrentFrame(0);
		m_animSprite->SetRenderLayer((unsigned int) a_pos.y / 44.f);

		float xsize = 40;
		float ysize = 30;
		Vec2 offset = Vec2(2, -(2 + ysize));
		ColliderComponent* colliderComp = AddComponent<ColliderComponent>(PolyShape::Rectangle(offset, Vec2(xsize, 0)));
		colliderComp->bounciness = 0;

		//Sprite* colliderSprite = AddComponent<Sprite>(RS__PIXEL_PNG);
		//colliderSprite->SetRenderLayer(0);
		//colliderSprite->SetDisplayMode(DisplayMode::TopLeft);
		//colliderSprite->SetSize(Vec2(xsize, ysize));
		//colliderSprite->SetLocalPosition(offset);
	}
};

