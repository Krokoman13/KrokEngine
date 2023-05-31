#pragma once
#include "../../Core/SceneManager/SceneManager.hpp"
#include "../../Essentials/Game.hpp"
#include "ColisionHandeling/CollisionCalculator.hpp"
#include "Components/TriggerColliderComponent.hpp"
#include "Components/RigidBody.hpp"

class PhysicsScene : public Scene
{
private:
	float _physicsSpeed = 10.0f;
	float _cycleSpeed;

public:
	using Scene::Scene;

	void PhysicsUpdate(Scene* pScene);

	virtual void HandleObjectsInScene() override
	{
		PhysicsUpdate(this);
		Scene::HandleObjectsInScene();
	}

private:
	void load(const std::vector<GameObject*>& pToLoad);
	void handleDestroyed(const std::vector<std::unique_ptr<GameObject>>& pToDestroy);
	void handleDestroyed(Component* component);

	void calculateVelocities();
	void moveRidgids(float pDuration = 1.0f);
	void applyVelocities(float pMultiplier = 1.0f);
	CollisionInfo moveRigid(RigidBody* pRigidBody, float pMultiplier = 1.0f);
	CollisionInfo getCollision(RigidBody* pRigidBody, ColliderComponent* collider, Vec2& desiredTranslation);

	const float _minToi = 0.1f;

	std::vector<TriggerColliderComponent*> _triggerObjects;
	std::vector<ColliderComponent*> _staticObjects;
	std::vector<RigidBody*> _rigidObjects;
};

