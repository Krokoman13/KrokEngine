#include "PhysicsObject.hpp"
#include "../../../Core/Graphics/ImageGameObject.hpp"

PhysicsObject::PhysicsObject(ColliderComponent* pComponent, Vec2 pPos) : GameObject(pPos, "PhysicsObject")
{
	collider = pComponent;
	AddComponent(collider);
}

PhysicsObject::PhysicsObject(std::vector<Vec2> pShape, Vec2 pPos) : PhysicsObject(new ColliderComponent(pShape), pPos)
{

}

PhysicsObject::PhysicsObject(CircleCollider* pCircle, Vec2 pPos) : PhysicsObject(new ColliderComponent(pCircle), pPos)
{
}

void PhysicsObject::ShowCollider()
{
	if (_collidersShown) return;

	for (CircleCollider* circle : collider->GetCircles())
	{
		float radius = circle->GetRadius();

		if (radius < 1.5f) continue;

		ImageGameObject* imageCircle = new ImageGameObject("Debug/GreenCircle.png", circle->GetCenter());
		imageCircle->centered = true;
		imageCircle->SetSize(radius, radius);
		AddChild(imageCircle);
	}

	for (LineCollider* line : collider->GetLines())
	{
		Vec2 lineVec = line->GetEnd() - line->GetStart();
		Vec2 middle = lineVec / 2.0f + line->GetStart();

		ImageGameObject* lineImage = new ImageGameObject("Debug/Greensquare.png", middle);
		lineImage->centered = true;
		lineImage->SetLocalRotation(lineVec.GetAngleRadians());
		lineImage->SetSize(lineVec.Length(), 1.0f);
		AddChild(lineImage);
	}

	_collidersShown = true;
}
