#pragma once
#include "../../../Essentials/GameObject.hpp"

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

