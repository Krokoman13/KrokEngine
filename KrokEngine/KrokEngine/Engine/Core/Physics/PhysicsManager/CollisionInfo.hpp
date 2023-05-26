#pragma once
#include "../../Math/Vec2.hpp"

class Collider;
class RigidBody;

struct CollisionInfo
{
	Collider* aCollider = nullptr;
	Collider* bCollider = nullptr;

	RigidBody* aRigidBody = nullptr;
	RigidBody* bRigidBody = nullptr;

	Vec2 aPOI = Vec2();
	Vec2 aVelocity = Vec2();

	Vec2 bPOI = Vec2();
	Vec2 bVelocity = Vec2();

	float TOI  = 1.0f;
}; 