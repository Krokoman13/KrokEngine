#include "TriggerColliderComponent.hpp"

TriggerColliderComponent::TriggerColliderComponent(CircleCollider* pToAdd) : ColliderComponent(pToAdd)
{
}

void TriggerColliderComponent::CollidesWith(RigidBody* pOther)
{
	if (IsColliding(pOther)) return;

	_colliding.push_back(pOther);

	if (!WasColliding(pOther)) onTriggerEnterAction(pOther);
}

void TriggerColliderComponent::Update()
{
	while (_collided.size() > 0)
	{
		RigidBody* collided = _collided[_collided.size() - 1];

		if (!IsColliding(collided)) onTriggerExitAction(collided);

		_collided.erase(_collided.end());
	}
	
	_collided = _colliding;
}


const bool TriggerColliderComponent::IsColliding() const
{
	return !_colliding.empty();
}

const bool TriggerColliderComponent::IsColliding(RigidBody* pOther) const
{
	for (RigidBody* colliding : _colliding)
	{
		if (pOther == colliding) return true;
	}

	return false;
}

const bool TriggerColliderComponent::WasColliding(RigidBody* pOther) const
{
	for (RigidBody* collided : _collided)
	{
		if (pOther == collided) return true;
	}

	return false;
}
