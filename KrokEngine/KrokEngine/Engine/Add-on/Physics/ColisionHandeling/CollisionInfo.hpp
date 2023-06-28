#pragma once
#include "../../../Core/Math/Vec2.hpp"

class Collider;
class RigidBody;

struct CollisionInfo
{
	Collider* collider1 = nullptr;
	Collider* collider2 = nullptr;

	RigidBody* rigidBody1 = nullptr;
	RigidBody* rigidBody2 = nullptr;

	Vec2 trans1 = Vec2();
	Vec2 trans2 = Vec2();

	Vec2 normal = Vec2();

	float TOI  = 1.0f;
}; 