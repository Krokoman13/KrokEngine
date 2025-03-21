#include "LineCollider.hpp"
#include "CircleCollider.hpp"
#include "../../../Core/Math/Vec2.hpp"

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

Vec2 LineCollider::GetLocalStart() const
{
	return _start.GetLocalPosition();
}

Vec2 LineCollider::GetLocalEnd() const
{
	return  _end.GetLocalPosition();
}
