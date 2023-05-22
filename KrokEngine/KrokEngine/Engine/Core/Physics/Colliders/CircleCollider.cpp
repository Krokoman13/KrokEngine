#include "CircleCollider.hpp"
#include "LineCollider.hpp"
#include "../ColliderComponent.hpp"

CircleCollider::CircleCollider(float radius, Vec2 offset) : _center(offset)
{
    _radius = radius;
}

bool CircleCollider::Colliding(const CircleCollider* pOther) const
{
    Vec2 diff = GetCenter() - pOther->GetCenter();
    float distance = diff.GetLength();
    float minDistance = pOther->GetRadius() + GetRadius();

    if (minDistance > distance)
    {
        return true;
    }

    return false;
}

bool CircleCollider::Colliding(const LineCollider* line) const
{
    // get length of the line
    Vec2 start = line->GetStart();
    Vec2 end = line->GetEnd();
    float len = (start - end).GetLength();

    Vec2 position = GetCenter();
    float dot = (((position.x - start.x) * (end.x - start.x)) + ((position.y - start.y) * (end.y - start.y))) / (len * len);

    Vec2 closest = start + dot * (end - start);
   
    float d1 = (closest - start).GetLength();
    float d2 = (closest - end).GetLength();

    // get the length of the line
    const float buffer = 0.1f;    // higher # = less accurate

    if (!(d1 + d2 >= len - buffer && d1 + d2 <= len + buffer))
    {
        return false;
    }

    // get distance to closest point
    Vec2 distanceVec = closest - position;

    if (distanceVec.GetLength() <= GetRadius())
    {
        return true;
    }

    return false;
}

void CircleCollider::SetParent(GameObject* pParent)
{
	_center.SetParent(pParent);
}

Vec2 CircleCollider::GetCenter() const
{
	return _center.GetGlobalPosition();
}

float CircleCollider::GetRadius() const
{
    Vec2 scale = _center.GetGlobalScale();
    return _radius * (scale.x + scale.y) / 2.0f;
}
