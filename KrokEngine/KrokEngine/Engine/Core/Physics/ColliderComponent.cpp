#include "ColliderComponent.hpp"

ColliderComponent::ColliderComponent(Collider* pToAdd)
{
	Add(pToAdd);
}

const std::vector<Collider*>& ColliderComponent::GetColliders() const
{
	return _colliders;
}

void ColliderComponent::Add(Collider* pCollider)
{
	if (pCollider == nullptr) return;
	pCollider->SetColliderComponent(this);
	_colliders.push_back(pCollider);
}

void ColliderComponent::SetGameObject(GameObject* pGameObject)
{
	for (Collider* collider : _colliders)
	{
		collider->SetParent(pGameObject);
	}
}

bool ColliderComponent::Colliding(const ColliderComponent& pOther) const
{
	const std::vector<Collider*>& others = pOther.GetColliders();

	for (Collider* mine : _colliders)
	{
		for (Collider* other : others) if (mine->Colliding(other)) return true;
	}

	return false;
}

bool ColliderComponent::IsExclusive()
{
	return true;
}
