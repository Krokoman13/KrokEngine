#include "TriggerColliderComponent.hpp"

void TriggerColliderComponent::CollidesWith(Collider* pOther)
{
	if (IsColliding(pOther)) return;

	_colliding.push_back(pOther);
	//std::cout << pOther->GetGameObject()->name << std::endl;

	if (onTriggerEnterAction && !WasColliding(pOther)) onTriggerEnterAction(pOther);
}

void TriggerColliderComponent::Update()
{
	while (_collided.size() > 0)
	{
		Collider* collided = _collided[_collided.size() - 1];

		if (onTriggerExitAction && !IsColliding(collided)) onTriggerExitAction(collided);

		_collided.erase(_collided.end() - 1);
	}
	
	_collided = _colliding;
	_colliding.clear();
}


bool TriggerColliderComponent::IsColliding() const
{
	return !_colliding.empty();
}


bool TriggerColliderComponent::IsColliding(Collider* pOther) const
{
	return std::find(_colliding.begin(), _colliding.end(), pOther) != _colliding.end();
}

bool TriggerColliderComponent::WasColliding(Collider* pOther) const
{
	return std::find(_collided.begin(), _collided.end(), pOther) != _collided.end();
}

void TriggerColliderComponent::EnterReport(GameObject* pSource, Collider* pCollider)
{
	std::cout << pSource->name << ", TriggerEnter: " << pCollider->GetColliderComponent()->GetGameObject()->name << std::endl;
}

void TriggerColliderComponent::ExitReport(GameObject* pSource, Collider* pCollider)
{
	std::cout << pSource->name << ", TriggerExit: " << pCollider->GetColliderComponent()->GetGameObject()->name << std::endl;
}
