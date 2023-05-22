#include "LineCollider.hpp"
#include "CircleCollider.hpp"
#include "../../Math/Vec2.hpp"

LineCollider::LineCollider(Vec2 pStart, Vec2 pEnd) : _start(pStart), _end(pEnd)
{
}

bool LineCollider::Colliding(const CircleCollider* pOther) const
{
	return pOther->Colliding(this);
}

bool LineCollider::Colliding(const LineCollider* pOther) const
{
	return false;
}

void LineCollider::SetParent(GameObject* pParent)
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
