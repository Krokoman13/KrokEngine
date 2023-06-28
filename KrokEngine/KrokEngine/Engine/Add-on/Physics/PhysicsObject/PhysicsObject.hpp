#pragma once
#include "../Components/RigidBody.hpp"

class PhysicsObject : public GameObject
{
public:
	PhysicsObject(std::vector<Vec2> pShape, Vec2 pPos = Vec2());
	PhysicsObject(CircleCollider* col, Vec2 pPos = Vec2());

	ColliderComponent* collider;

	void ShowCollider();

private:
	PhysicsObject(ColliderComponent* pCollider, Vec2 pPos);
	bool _collidersShown = false;
};

