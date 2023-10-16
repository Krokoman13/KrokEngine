#pragma once
#include "ColliderComponent.hpp"
#include "RigidBody.hpp"
#include <functional>

/// <summary>
/// Component to check for collisions, does not keep track of those collisions currently! 
/// Only if there are any!
/// </summary>

class TriggerColliderComponent : public ColliderComponent
{
private:
	std::vector<RigidBody*> _collided;
	std::vector<RigidBody*>_colliding;

public:
	TriggerColliderComponent(CircleCollider* pToAdd = nullptr);

public:
	std::function<void(RigidBody*)> onTriggerEnterAction;
	std::function<void(RigidBody*)> onTriggerExitAction;

public:
	void CollidesWith(RigidBody* pOther);

	virtual void Update() override;

	bool IsColliding() const;
	bool IsColliding(RigidBody* pOther) const;
	bool WasColliding(RigidBody* pOther) const;
	const std::vector<RigidBody*>& Colliding() const;
};

