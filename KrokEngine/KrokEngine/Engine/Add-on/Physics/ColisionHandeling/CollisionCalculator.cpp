#include "CollisionCalculator.hpp"
#include "../Components/ColliderComponent.hpp"
#include <cmath>

CollisionInfo CollisionCalculator::CalculateCollision
    (CircleCollider* pCircle, const Vec2 pTranslation, LineCollider* pLine)
{
	CollisionInfo outp;

    const Vec2 circleOldPosition = pCircle->GetCenter();
    const float circleRadius = pCircle->GetRadius();

    const Vec2 lineStart = pLine->GetStart();
    const Vec2 lineEnd = pLine->GetEnd();

    const Vec2 oldDiffVec = circleOldPosition - lineStart;
    const Vec2 lineVector = lineStart - lineEnd;
    const Vec2 lineNormal = lineVector.Normal();

    const float a = lineNormal.Dot(oldDiffVec) - circleRadius;    //Start distance
    const float b = -(lineNormal.Dot(pTranslation));  //Movement allong normal axis

    if (b <= 0.0f) return outp;

    float TOI;

    if (a >= 0.0f) {
        TOI = a / b;
    }
    else if (a >= -circleRadius) {
        TOI = a / b;
    }
    else {
        return outp;
    }

    if (TOI <= 1.0f)
    {
        const Vec2 POI = circleOldPosition + pTranslation * TOI;
        const float distance = (lineStart - POI).Dot(lineVector.Normalized());

        if (distance > 0 && distance < lineVector.Length())
        {
            outp.collider1 = pCircle;
            outp.collider2 = pLine;

            //outp.trans1 = pTranslation * TOI;
            outp.TOI = TOI;

            outp.normal = lineNormal;

            return outp;
        }
    }

	return outp;
}

CollisionInfo CollisionCalculator::CalculateCollision
    (CircleCollider* pCircle, const Vec2 pTranslation1, LineCollider* pLine, const Vec2 pTranslation2)
{
    CollisionInfo outp;

    const Vec2 circleOldPosition = pCircle->GetCenter();
    const float circleRadius = pCircle->GetRadius();

    const Vec2 lineOldStart = pLine->GetStart();
    const Vec2 lineOldEnd = pLine->GetEnd();

    const Vec2 circleNewPosition = circleOldPosition + pTranslation1;
    const Vec2 lineNewStart = lineOldStart + pTranslation2;
    const Vec2 lineNewEnd = lineOldEnd + pTranslation2;

    const Vec2 circleTranslation = pTranslation1 - pTranslation2;
    const Vec2 lineTranslation = -circleTranslation;

    const Vec2 circleRelativePosition = circleNewPosition - lineOldStart;
    const Vec2 lineRelativePosition = lineNewStart - lineNewEnd;

    const Vec2 lineNormal = lineRelativePosition.Normal();

    const float a = lineNormal.Dot(circleRelativePosition) - circleRadius;

    const float b = -(lineNormal.Dot(circleTranslation));

    if (b <= 0.0f) return outp;

    float TOI;

    if (a >= 0.0f)
    {
        TOI = a / b;
    }
    else if (a >= -circleRadius)
    {
        TOI = a / b;
    }
    else return outp;

    if (TOI <= 1.0f)
    {
        const Vec2 POI = circleOldPosition + pTranslation1 * TOI;
        const float distance = (lineNewStart - POI).Dot(lineRelativePosition.Normalized());

        if (distance > 0 && distance < lineRelativePosition.Length())
        {
            outp.collider1 = pCircle;
            outp.collider2 = pLine;

            //outp.trans1 = pTranslation1 * TOI;
            //outp.trans2 = pTranslation2 * TOI;

            outp.TOI = TOI;

            outp.normal = lineNormal;
        }
    }

    return outp;
}

CollisionInfo CollisionCalculator::CalculateCollision
    (CircleCollider* pCircle1, const Vec2 pTranslation1, CircleCollider* pCircle2)
{
    CollisionInfo outp;

    const float r1 = pCircle1->GetRadius();
    const float r2 = pCircle2->GetRadius();
    const Vec2 p1 = pCircle1->GetCenter();
    const Vec2 p2 = pCircle2->GetCenter();

    const Vec2 u = p1 - p2;     //Relative position
    const Vec2 v = pTranslation1;

    const float b = 2 * u.Dot(v);
    const float c = sqr(u.Length()) - sqr(r1 + r2);

    if (c < 0.0f) {
        if (b >= 0.0f) return outp;

        outp.collider1 = pCircle1;
        outp.collider2 = pCircle2;

        outp.TOI = 0.0f;
        
        const Vec2 normal = u.Normalized();
        outp.normal = normal;

        return outp;
    }

    const float a = sqr(v.Length());

    if (abs(a) < 0.001f) return outp;

    const float D = sqr(b) - (4.0f * a * c);

    if (D < 0.0f) return outp;

    const float t = (-b - sqrt(D)) / (2 * a);

    if (0.0f <= t && t < 1.0f) {
        outp.collider1 = pCircle1;
        outp.collider2 = pCircle2;

        outp.TOI = t;

        const Vec2 translation = pTranslation1 * t;
        //outp.trans1 = translation;

        const Vec2 POI = p1 + translation;
        const Vec2 normal = (POI - p2).Normalized();
        
        outp.normal = normal;
    }

    return outp;
}

CollisionInfo CollisionCalculator::CalculateCollision
    (CircleCollider* pCircle1, const Vec2 pTranslation1, CircleCollider* pCircle2, const Vec2 pTranslation2)
{
    CollisionInfo outp;

    const float r1 = pCircle1->GetRadius();
    const float r2 = pCircle2->GetRadius();
    const Vec2 p1 = pCircle1->GetCenter() + pTranslation1; // Update position with translation
    const Vec2 p2 = pCircle2->GetCenter() + pTranslation2; // Update position with translation

    const Vec2 u = p1 - p2;     // Relative position
    const Vec2 v = pTranslation1 - pTranslation2; // Relative velocity

    const float b = 2 * u.Dot(v);
    const float c = sqr(u.Length()) - sqr(r1 + r2);

    if (c < 0.0f)
    {
        if (b >= 0.0f) return outp;

        outp.collider1 = pCircle1;
        outp.collider2 = pCircle2;

        outp.TOI = 0.0f;

        const Vec2 normal = u.Normalized();

        outp.normal = normal;

        return outp;
    }

    const float a = sqr(v.Length());

    if (abs(a) < 0.001f) return outp;

    const float D = sqr(b) - (4.0f * a * c);

    if (D < 0.0f) return outp;

    const float t = (-b - sqrt(D)) / (2 * a);

    if (0.0f <= t && t < 1.0f)
    {
        outp.collider1 = pCircle1;
        outp.collider2 = pCircle2;

        //outp.trans1 = pTranslation1 * t;
        //outp.trans2 = pTranslation2 * t;
        outp.TOI = t;

        const Vec2 POI1 = p1 + pTranslation1 * t;
        const Vec2 POI2 = p2 + pTranslation2 * t;

        const Vec2 normal = (POI1 - POI2).Normal();
        outp.normal = normal;
    }

    return outp;
}

float CollisionCalculator::sqr(const float& pValue)
{
    return pValue * pValue;
}
