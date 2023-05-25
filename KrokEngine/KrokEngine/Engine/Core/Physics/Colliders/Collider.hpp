#pragma once
#include "../../../Essentials/GameObject.hpp"
//#include "CollisionInfo.hpp"

class LineCollider;
class CircleCollider;
class ColliderComponent;

class Collider
{
public: 
	virtual void SetParent(Transform* pParent) = 0;

	void SetColliderComponent(ColliderComponent* pGameObject);
	ColliderComponent* GetColliderComponent() const;

private:
	ColliderComponent* _colliderComponent = nullptr;
};

