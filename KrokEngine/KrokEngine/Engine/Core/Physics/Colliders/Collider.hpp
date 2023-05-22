#pragma once
#include "../../../Essentials/GameObject.hpp"
//#include "CollisionInfo.hpp"

class LineCollider;
class CircleCollider;
class ColliderComponent;

class Collider
{
public: 
	virtual bool Colliding(const CircleCollider* pOther) const = 0;
	virtual bool Colliding(const LineCollider* pOther) const = 0;

	bool Colliding(const Collider* pOther) const;

	virtual void SetParent(GameObject* pParent);

	void SetColliderComponent(ColliderComponent* pGameObject);
	ColliderComponent* GetColliderComponent() const;

private:
	ColliderComponent* _colliderComponent;
};

