#include "LineCollider.hpp"
#include "CircleCollider.hpp"
#include "../../Math/Vec2.hpp"

LineCollider::LineCollider(Vec2 pStart, Vec2 pEnd) : _start(pStart), _end(pEnd)
{
}

void LineCollider::SetParent(Transform* pParent)
{
	_start.SetParent(pParent);
	_end.SetParent(pParent);
}

Vec2 LineCollider::GetStart() const
{
	return _start.GetGlobalPosition();
}

Vec2 LineCollider::GetEnd() const
{
	return _end.GetGlobalPosition();
}
