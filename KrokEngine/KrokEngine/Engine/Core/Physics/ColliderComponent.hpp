#pragma once
#include "../../Essentials/Component.hpp"
#include "Colliders/Collider.hpp"

class ColliderComponent : public Component
{
public:
	ColliderComponent(Collider* toAdd = nullptr);

	const std::vector<Collider*>& GetColliders() const;

	void Add(Collider* pCollider);
	virtual void SetGameObject(GameObject* pGameObject);

	bool Colliding(const ColliderComponent& pOther) const;

	bool IsExclusive() override;

private:
	std::vector<Collider*> _colliders;
};

