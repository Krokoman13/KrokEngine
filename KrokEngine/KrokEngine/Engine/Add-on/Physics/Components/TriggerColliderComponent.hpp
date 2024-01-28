#pragma once
#include "ColliderComponent.hpp"
#include <functional>
#include <vector>

/// <summary>
/// Component to check for collisions, does not keep track of those collisions currently! 
/// Only if there are any!
/// </summary>

class TriggerColliderComponent : public ColliderComponent
{
private:
	std::vector<Collider*> _collided = std::vector<Collider*>();
	std::vector<Collider*>_colliding = std::vector<Collider*>();

public:
	using ColliderComponent::ColliderComponent;

public:
	std::function<void(Collider*)> onTriggerEnterAction = nullptr;
	std::function<void(Collider*)> onTriggerExitAction = nullptr;

public:
	void CollidesWith(Collider* pOther);

	virtual void Update() override;

	bool IsColliding() const;
	bool IsColliding(Collider* pOther) const;
	bool WasColliding(Collider* pOther) const;

	static void EnterReport(GameObject* pSource, Collider* pCollider);
	static void ExitReport(GameObject* pSource, Collider* pCollider);
	//const std::vector<ColliderComponent*>& Colliding() const;
};

