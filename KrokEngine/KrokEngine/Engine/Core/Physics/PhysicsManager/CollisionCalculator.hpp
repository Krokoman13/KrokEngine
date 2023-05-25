#pragma once
#include "CollisionInfo.hpp"
#include "../Colliders/LineCollider.hpp"
#include "../Colliders/CircleCollider.hpp"

class CollisionCalculator
{
public:
	static CollisionInfo CalculateCollision(CircleCollider* pCircle, const Vec2& pTranslation, LineCollider* pLine);
};

