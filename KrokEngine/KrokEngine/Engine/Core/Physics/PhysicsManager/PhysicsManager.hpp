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
	void Load(const std::vector<GmObjctPtr>& pToLoad);

private:
	void cleanTriggers();
	void cleanStatics();
	void cleanRigids();

	void updateRigids(float pDuration = 1.0f);
	void applyVelocity(float pMultiplier = 1.0f);
	CollisionInfo updateRigid(RigidBody* pRigidBody, float pMultiplier = 1.0f);
	CollisionInfo getCollision(RigidBody* pRigidBody, ColliderComponent* collider, Vec2& desiredTranslation);

	Game* _game;
	float _physicsSpeed = 10.0f;
	float _cycleSpeed;
	const float _minToi = 0.01f;

	std::vector<TriggerColliderComponent*> _triggerObjects;
	std::vector<ColliderComponent*> _staticObjects;
	std::vector<RigidBody*> _rigidObjects;
};

