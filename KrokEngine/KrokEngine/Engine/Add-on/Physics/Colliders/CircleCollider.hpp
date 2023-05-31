#pragma once
#include "Collider.hpp"
#include "../../../Core/Math/Vec2.hpp"

class CircleCollider : public Collider
{
public:
	CircleCollider(float pRadius, Vec2 pOffset = Vec2(0.0f, 0.0f));

	void SetParent(Transform* pParent) override;

	Vec2 GetCenter() const;
	float GetRadius() const;

private:
	Transform _center;
	float _radius;
};

