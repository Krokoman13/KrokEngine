#pragma once
#include "../../Math/Vec2.hpp"
#include <limits>

class Collider;
class RigidBody;

struct CollisionInfo
{
	bool collided = false;

	Collider* aCollider = nullptr;
	Collider* bCollider = nullptr;

	RigidBody* aRigidBody = nullptr;
	RigidBody* bRigidBody = nullptr;

	Vec2 aTranslation = Vec2();
	Vec2 aVelocity = Vec2();

	Vec2 bTranslation = Vec2();
	Vec2 bVelocity = Vec2();

	float TOI  = std::numeric_limits<float>().max();
}; 