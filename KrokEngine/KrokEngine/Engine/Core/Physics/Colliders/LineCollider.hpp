#pragma once
#include "Collider.hpp"

class LineCollider : public Collider
{
public:
	LineCollider(Vec2 start, Vec2 end);
	bool Colliding(const CircleCollider* pOther) const override;
	bool Colliding(const LineCollider* pOther) const override;

	void SetParent(GameObject* pParent) override;

	Vec2 GetStart() const;
	Vec2 GetEnd() const;

private:
	Transform _start;
	Transform _end;
};

