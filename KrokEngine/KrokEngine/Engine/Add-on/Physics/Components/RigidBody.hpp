#pragma once
#include "ColliderComponent.hpp"

class RigidBody : public ColliderComponent
{
public:
	using ColliderComponent::ColliderComponent;

public:
	Vec2 velocity;
	Vec2 acceleration;
	float weight = 1.0f;
	bool hasGravity = false;
};

