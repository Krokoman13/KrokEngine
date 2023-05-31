#pragma once
#include "../Components/TriggerColliderComponent.hpp"
#include "../Components/ColliderComponent.hpp"
#include "../Components/RigidBody.hpp"
#include "CollisionCalculator.hpp"

class Game;

class PhysicsManager
{
public:
	PhysicsManager(Game* pGame);
	void Update(Scene* pScene);
	void Load(const std::vector<GameObject*>& pToLoad);

private:
	void calculateVelocities();
	void moveRidgids(float pDuration = 1.0f);
	void applyVelocities(float pMultiplier = 1.0f);
	CollisionInfo moveRigid(RigidBody* pRigidBody, float pMultiplier = 1.0f);
	CollisionInfo getCollision(RigidBody* pRigidBody, ColliderComponent* collider, Vec2& desiredTranslation);

	Game* _game;
	float _physicsSpeed = 10.0f;
	float _cycleSpeed;
	const float _minToi = 0.1f;

	std::vector<TriggerColliderComponent*> _triggerObjects;
	std::vector<ColliderComponent*> _staticObjects;
	std::vector<RigidBody*> _rigidObjects;
};

