#pragma once
#include "TriggerColliderComponent.hpp"

class RigidBody : public TriggerColliderComponent
{
public:
	RigidBody(CircleCollider* toAdd);
	RigidBody(const std::vector<Vec2>& pPoints);

public:
	Vec2 velocity = Vec2();
	Vec2 acceleration = Vec2();
	float weight = 1.0f;
	bool hasGravity = false;
};

