#pragma once
#include "ColliderComponent.hpp"

class RigidBody : public ColliderComponent
{
public:
	RigidBody(CircleCollider* pCollider = nullptr);
	virtual ~RigidBody();

public:
	Vec2 velocity;
	Vec2 acceleration;
};

