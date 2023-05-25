#include "CollisionCalculator.hpp"
#include "../Components/ColliderComponent.hpp"

CollisionInfo CollisionCalculator::CalculateCollision(CircleCollider* pCircle, const Vec2& pTranslation, LineCollider* pLine)
{
	CollisionInfo outp;

    Vec2 velocity = pTranslation;
    Vec2 circleOldPosition = pCircle->GetCenter();
    float circleRadius = pCircle->GetRadius();

    Vec2 lineStart = pLine->GetStart();
    Vec2 lineEnd = pLine->GetEnd();

    Vec2 oldDiffVec = circleOldPosition - lineStart;
    Vec2 lineVector = lineStart - lineEnd;
    Vec2 lineNormal = lineVector.Normal();

    float a = lineNormal.Dot(oldDiffVec) - circleRadius;    //Start distance
    float b = -(lineNormal.Dot(pTranslation));  //Movement allong normal axis

    if (b <= 0.0f) return outp;

    float TOI;

    if (a >= 0.0f)
    {
        TOI = a / b;
    }
    else if (a >= -circleRadius)
    {
        TOI = 0.0f;
    }
    else return outp;

    Vec2 POI;
    if (TOI <= 1.0f)
    {
        Vec2 translation = pTranslation * TOI;
        POI = circleOldPosition + translation;
        float distance = (lineStart - POI).Dot(lineVector.Normalized());

        if (distance > 0 && distance < lineVector.GetLength())
        {
            outp.aCollider = pCircle;
            outp.bCollider = pLine;

            outp.TOI = TOI;
            outp.collided = true;
            outp.aTranslation = translation;

            float bounciness = pCircle->GetColliderComponent()->GetBounciness();
            bounciness += pLine->GetColliderComponent()->GetBounciness();
            bounciness /= 2.0f;
            outp.aVelocity = velocity.Reflected(lineNormal, bounciness);
        }
    }

	return outp;
}
