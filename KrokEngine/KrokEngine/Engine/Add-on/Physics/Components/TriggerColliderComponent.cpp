#include "TriggerColliderComponent.hpp"

TriggerColliderComponent::TriggerColliderComponent(CircleCollider* pToAdd) : ColliderComponent(pToAdd)
{
}

void TriggerColliderComponent::CollidesWith(RigidBody* pOther)
{
	if (IsColliding(pOther)) return;

	_colliding.push_back(pOther);
	//std::cout << pOther->GetGameObject()->name << std::endl;

	if (!WasColliding(pOther)) onTriggerEnterAction(pOther);
}

void TriggerColliderComponent::Update()
{
	while (_collided.size() > 0)
	{
		RigidBody* collided = _collided[_collided.size() - 1];

		if (!IsColliding(collided)) onTriggerExitAction(collided);

		_collided.erase(_collided.end() - 1);
	}
	
	_collided = _colliding;
	_colliding.clear();
}


bool TriggerColliderComponent::IsColliding() const
{
	return !_colliding.empty();
}

bool TriggerColliderComponent::IsColliding(RigidBody* pOther) const
{
	return std::find(_colliding.begin(), _colliding.end(), pOther) != _colliding.end();
}

bool TriggerColliderComponent::WasColliding(RigidBody* pOther) const
{
	return std::find(_collided.begin(), _collided.end(), pOther) != _collided.end();
}
