#include "PhysicsLine.hpp"

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
	AddComponent(colliderComp);

	_start = new ImageGameObject("Debug/Bluecircle.png", pStart.x, pStart.y);
	_start->centered = true;
	_start->SetSize(thickness, thickness);
	AddChild(_start);

	_end = new ImageGameObject("Debug/Bluecircle.png", pEnd.x, pEnd.y);
	_end->centered = true;
	_end->SetSize(thickness, thickness);
	AddChild(_end);

	_inbetween = new ImageGameObject("Debug/Greensquare.png");
	_inbetween->centered = true;
	_inbetween->SetLocalRotation(line.GetAngleRadians());
	_inbetween->SetSize(line.GetLength(), thickness);
	AddChild(_inbetween);
}
