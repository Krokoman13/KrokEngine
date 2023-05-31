#pragma once
#include "../Components/TriggerColliderComponent.hpp"
#include "../Components/ColliderComponent.hpp"
#include "../Components/RigidBody.hpp"
#include "CollisionCalculator.hpp"

class Game;

class PhysicsManager
{
public:
	PhysicsManager();
	void Update(Scene* pScene);

	float physicsSpeed = 10.0f;
	float cycleSpeed;

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

