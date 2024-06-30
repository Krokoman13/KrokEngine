#pragma once
#include "../Engine/Add-on/Physics.hpp"
#include "../Engine/KrokEngine.hpp"
#include "Components/GridLayerer.hpp"
#include "Components/Health.hpp"
#include "Components/Burnable.hpp"

#include "../Testing/UpdateComponent.hpp"

class Bomb : public GameObject
{
private:
	AnimationSprite* m_bomb;
	AnimationSprite* m_explosion;

public:
	Bomb(const Vec2 a_target)
	{
		m_bomb = AddComponent<AnimationSprite>(RS__BOMB_ANIM_SPRITESHEET_PNG, 10, 1, false);
		m_bomb->SetDisplayMode(DisplayMode::Center);

		m_explosion = AddComponent<AnimationSprite>(RS__EXPLOSION_ANIM_SPRITESHEET_PNG, 7, 1, false);
		m_explosion->SetDisplayMode(DisplayMode::Center);
		m_explosion->SetRenderLayer(1000);
		m_explosion->SetActive(false);

		AnimationSprite* bombCopy = m_bomb;
		AnimationSprite* explosionCopy = m_explosion;
		m_bomb->AddAnimation(Animation(0, 9, 0.1f, 
			[bombCopy, explosionCopy]() { 
				bombCopy->SetActive(false); 
				explosionCopy->SetActive(true); 
			}
		), "Charging");

		unsigned int explosionAnimID = m_explosion->AddAnimation(Animation(0, 6, 0.1f, [this]() { this->LateDestroy(); }), "Explodify");
		m_explosion->GetAnimation("Explodify").AddFunctionOnFrame(0, 
			[explosionCopy]() {
				explosionCopy->SetLocalScale(3); 
			}
		);
		m_explosion->GetAnimation(explosionAnimID).AddFunctionOnFrame(2,
			[this]() {
				this->explode();
			}
		);

		UpdateComponent* updateComponent = AddComponent<UpdateComponent>(
			[this, a_target]() {
				Vec2 diff = a_target - this->GetGlobalPosition();
				if (diff.Length() < 1) return;
				this->GlobalTranslate(diff * 0.01f);
			}
		);

		AddComponent<GridLayerer>();
	}

private:
	void explode() {

		PhysicsScene* pPhysicsScene = dynamic_cast<PhysicsScene*>(GetScene());

		if (!pPhysicsScene) return;

		GameObject* previous = nullptr;

		for (Collider* colliding : pPhysicsScene->OverLayCircle(this, 24))
		{
			GameObject* current = colliding->GetColliderComponent()->GetGameObject();

			if (current == previous) continue;
			previous = current;

			if (current == GetParent()) continue;

			Burnable* burnable = nullptr;
			if (!current->TryGetComponent<Burnable>(burnable)) continue;
			burnable->StartBurning(3, 1);
		}
	}
};
