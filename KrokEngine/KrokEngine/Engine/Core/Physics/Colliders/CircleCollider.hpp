#pragma once
#include "Collider.hpp"
#include "../../Math/Vec2.hpp"

class CircleCollider : public Collider
{
public:
	CircleCollider(float pRadius, Vec2 pOffset = Vec2(0.0f, 0.0f));

	virtual bool Colliding(const CircleCollider* pOther) const override;
	virtual bool Colliding(const LineCollider* pOther) const override;

	void SetParent(GameObject* pParent) override;

	Vec2 GetCenter() const;
	float GetRadius() const;

private:
	Transform _center;
	float _radius;
};

