#include "CollisionCalculator.hpp"
#include "../Components/ColliderComponent.hpp"
#include <cmath>

CollisionInfo CollisionCalculator::CalculateCollision(CircleCollider* pCircle, const Vec2& pTranslation, LineCollider* pLine)
{
	CollisionInfo outp;

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
        POI = circleOldPosition + pTranslation * TOI;
        float distance = (lineStart - POI).Dot(lineVector.Normalized());

        if (distance > 0 && distance < lineVector.Length())
        {
            outp.aCollider = pCircle;
            outp.bCollider = pLine;

            outp.TOI = TOI;
            outp.aPOI = POI;

            float bounciness = pCircle->GetColliderComponent()->GetBounciness();
            bounciness += pLine->GetColliderComponent()->GetBounciness();
            bounciness /= 2.0f;
            outp.aVelocity = pTranslation.Reflected(lineNormal, bounciness);
        }
    }

	return outp;
}

CollisionInfo CollisionCalculator::CalculateCollision(CircleCollider* pCircle1, const Vec2& pTranslation, CircleCollider* pCircle2)
{
    CollisionInfo outp;

    float r1 = pCircle1->GetRadius();
    float r2 = pCircle2->GetRadius();
    Vec2 p = pCircle1->GetCenter();
    Vec2 q = pCircle2->GetCenter();

    Vec2 u = p - q;     //Relative position
    Vec2 v = pTranslation;

    float b = 2 * u.Dot(v);
    float c = sqr(u.Length()) - sqr(r1 + r2);

    if (c < 0.0f)
    {
        if (b >= 0.0f) return outp;

        outp.aCollider = pCircle1;
        outp.bCollider = pCircle2;

        outp.TOI = 0.0f;
        outp.aPOI = q + u.Normalized() * (r1 + r2);

        return outp;
    }

    float a = sqr(v.Length());

    if (abs(a) < 0.001f) return outp;

    float D = sqr(b) - (4.0f * a * c);

    if (D < 0.0f) return outp;

    float t = (-b - sqrt(D)) / (2 * a);

    if (0.0f <= t && t < 1.0f)
    {
        outp.aCollider = pCircle1;
        outp.bCollider = pCircle2;

        outp.TOI = t;

        Vec2 POI = p + pTranslation * t;
        outp.aPOI = POI;

        Vec2 normal = (POI - q).Normalized();
        
        float bounciness = pCircle1->GetColliderComponent()->GetBounciness();
        bounciness += pCircle2->GetColliderComponent()->GetBounciness();
        bounciness /= 2.0f;
        outp.aVelocity = pTranslation.Reflected(normal, bounciness);
    }

    return outp;
}

float CollisionCalculator::sqr(const float& pValue)
{
    return pValue * pValue;
}
