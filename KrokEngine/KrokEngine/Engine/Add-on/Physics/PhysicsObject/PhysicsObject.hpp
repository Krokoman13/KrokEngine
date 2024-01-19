#pragma once
#include "../../../Engine/Essentials/GameObject.hpp"

class CircleCollider;
class ColliderComponent;


class PhysicsObject : public GameObject
{
public:
	PhysicsObject(std::vector<Vec2> pShape, Vec2 pPos = Vec2());
	PhysicsObject(CircleCollider* col, Vec2 pPos = Vec2());

	ColliderComponent* collider;

	void ShowCollider();

private:
	bool _collidersShown = false;
};

