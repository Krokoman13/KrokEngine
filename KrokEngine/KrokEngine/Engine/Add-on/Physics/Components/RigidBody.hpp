#pragma once
#include "TriggerColliderComponent.hpp"

class RigidBody : public TriggerColliderComponent
{
public:
	RigidBody() : TriggerColliderComponent() {};
	RigidBody(CircleCollider* a_circleCollider) : TriggerColliderComponent(a_circleCollider) {};
	RigidBody(LineCollider* a_lineCollider) : TriggerColliderComponent(a_lineCollider) {};
	RigidBody(const std::vector<Vec2>& a_points) : TriggerColliderComponent(a_points) {};

public:
	Vec2 velocity = Vec2();
	Vec2 acceleration = Vec2();
	float weight = 1.0f;
	bool hasGravity = false;
};

