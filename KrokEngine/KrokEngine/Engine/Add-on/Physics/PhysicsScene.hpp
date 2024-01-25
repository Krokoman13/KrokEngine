#pragma once
#include "../../Core/SceneManager/SceneManager.hpp"
#include "../../Essentials/Game.hpp"
#include "ColisionHandeling/CollisionCalculator.hpp"
#include "Components/TriggerColliderComponent.hpp"
#include "Components/RigidBody.hpp"

class PhysicsScene : public Scene
{
public:
	using Scene::Scene;

protected:
	Vec2 _gravity = Vec2(0, 9.81f);
	float _physicsSpeed = 5.0f;
	float _resistanceCoefficient = 0.04f;

private:
	float _cycleSpeed;

public:
	void PhysicsUpdate();

	virtual void HandleObjectsInScene() override
	{
		load(ToLoad());
		handleDestroyed(ToDestroy());

		Scene::HandleObjectsInScene();

		PhysicsUpdate();
	}

private:
	const float _minToi = 0.1f;

	std::vector<TriggerColliderComponent*> _triggerObjects;
	std::vector<ColliderComponent*> _staticObjects;
	std::vector<RigidBody*> _rigidObjects;

private:
	void load(const std::vector<GameObject*>& pToLoad);
	void load(Component* pToLoad);
	void handleDestroyed(const std::vector<std::unique_ptr<GameObject>>& pToDestroy);
	void handleDestroyed(Component* pComponent);

	void calculateVelocities();
	void checkRigids(const float pDuration = 1.0f);
	void applyVelocities(const float pMultiplier = 1.0f);
	static void resolveCollision(const CollisionInfo& pCollision);
	static void resolveCollision(RigidBody* pRigidBody1, RigidBody* pRigidbody2,const Vec2& pNormal);
	static void resolveCollision(RigidBody* pRigidBody, Collider* pCol, const Vec2& pNormal);
	static float calculateBounciness(ColliderComponent* pA, ColliderComponent* pB);
	CollisionInfo checkRigid(RigidBody* pRigidBody, const float pMultiplier, unsigned int pChecked);
	static CollisionInfo getCollision(RigidBody* pRigidBody, const Vec2& pDesiredTranslation, ColliderComponent* pStaticCollider);
	static CollisionInfo getCollision(RigidBody* pRigidBody1, const Vec2& pDesTran1, RigidBody* pRigidBody2, const Vec2& pDestran2, const float minToi);

	virtual void clearScene() override;
};

