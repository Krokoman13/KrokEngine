#include "PhysicsLine.hpp"
#include "../Engine/Add-on/Physics.hpp"

PhysicsLine::PhysicsLine(Vec2 pStart, Vec2 pEnd) : GameObject("PhysicsLine")
{
	Vec2 line = pEnd - pStart;
	Vec2 middle = line / 2.0f + pStart;
	SetLocalPosition(middle);

	float thickness = 1.0f;

	pEnd = pEnd - middle;
	pStart = pStart - middle;

	ColliderComponent* colliderComp = new ColliderComponent();
	colliderComp->Add(new LineCollider(pStart, pEnd));
	colliderComp->Add(new LineCollider(pEnd, pStart));
	colliderComp->Add(new CircleCollider(0.0f, pStart));
	colliderComp->Add(new CircleCollider(0.0f, pEnd));
	AddComponent(colliderComp);

	_inbetween = new ImageGameObject("Debug/Greensquare.png");
	_inbetween->centered = true;
	_inbetween->SetLocalRotation(line.GetAngleRadians());
	_inbetween->SetSize(line.Length(), thickness);
	_inbetween->SetRenderLayer(1);
	AddChild(_inbetween);
}
