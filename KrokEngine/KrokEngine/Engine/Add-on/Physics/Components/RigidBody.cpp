#include "RigidBody.hpp"

RigidBody::RigidBody(CircleCollider* toAdd) : TriggerColliderComponent(toAdd)
{
}

RigidBody::RigidBody(const std::vector<Vec2>& pPoints) : TriggerColliderComponent(pPoints)
{
}