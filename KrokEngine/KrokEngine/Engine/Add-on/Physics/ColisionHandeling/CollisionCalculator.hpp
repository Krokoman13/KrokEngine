#pragma once
#include "CollisionInfo.hpp"
#include "../Colliders/LineCollider.hpp"
#include "../Colliders/CircleCollider.hpp"

class CollisionCalculator
{
public:
	static CollisionInfo CalculateCollision(CircleCollider* pCircle, const Vec2 pTranslation, LineCollider* pLine);
	static CollisionInfo CalculateCollision(CircleCollider* pCircle, const Vec2 pTranslation1, LineCollider* pLine, const Vec2 pTranslation2);

	static CollisionInfo CalculateCollision(CircleCollider* pCircle1, const Vec2 pTranslation, CircleCollider* pCircle2);
	static CollisionInfo CalculateCollision(CircleCollider* pCircle1, const Vec2 pTranslation1, CircleCollider* pCircle2, const Vec2 pTranslation2);

private:
	static float sqr(const float& pValue);
};

