#include "CircleCollider.hpp"
#include "LineCollider.hpp"
#include "../Components/ColliderComponent.hpp"

CircleCollider::CircleCollider(float radius, Vec2 offset) : _center(offset)
{
    _radius = radius;
}

void CircleCollider::SetParent(Transform* pParent)
{
	_center.SetParent(pParent);
}

Vec2 CircleCollider::GetCenter() const
{
	return _center.GetGlobalPosition();
}

Vec2 CircleCollider::LocalCenter() const
{
    return _center.GetLocalPosition();
}

float CircleCollider::GetRadius() const
{
    Vec2 scale = _center.GetGlobalScale();
    return _radius * (scale.x + scale.y) / 2.0f;
}
