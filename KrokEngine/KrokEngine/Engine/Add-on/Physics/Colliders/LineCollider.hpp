#pragma once
#include "Collider.hpp"

class LineCollider : public Collider
{
public:
	LineCollider(Vec2 start, Vec2 end);

	void SetParent(Transform* pParent) override;

	Vec2 GetStart() const;
	Vec2 GetEnd() const;

	Vec2 GetLocalStart() const;
	Vec2 GetLocalEnd() const;

private:
	Transform _start;
	Transform _end;
};

