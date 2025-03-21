#include "PhysicsObject.hpp"
#include "../Components/ColliderComponent.hpp"
#include "../../../Core/Graphics/Core/Sprite/Sprite.hpp"
#include "../../../Assets/fileIndex.hpp"

PhysicsObject::PhysicsObject(std::vector<Vec2> pShape, Vec2 pPos) : GameObject(pPos, "PhysicsObject")
{
	collider = AddComponent<ColliderComponent>(pShape);
}

PhysicsObject::PhysicsObject(CircleCollider* pCircle, Vec2 pPos) : GameObject(pPos)
{
	collider = AddComponent<ColliderComponent>(pCircle);
}

void PhysicsObject::ShowCollider()
{
	if (_collidersShown) return;

	for (CircleCollider* circle : collider->GetCircles())
	{
		float radius = circle->GetRadius();

		if (radius < 1.5f) continue;

		Sprite* sprite = AddComponent<Sprite>(RS__BALL_PNG);
		sprite->diffuseColor = Color(0, 255, 0);
		sprite->SetLocalPosition(circle->LocalCenter());
		sprite->SetDisplayMode(DisplayMode::Center);
		sprite->SetLocalScale(Vec2(radius, radius) * 2);
	}

	for (LineCollider* line : collider->GetLines())
	{
		Vec2 lineVec = line->GetLocalStart() - line->GetLocalEnd();
		Vec2 middle = lineVec / 2.0f + line->GetLocalEnd();

		Sprite* sprite = AddComponent<Sprite>(RS__PIXEL_PNG);
		sprite->SetFilter(GL_NEAREST, GL_NEAREST);
		sprite->diffuseColor = Color(0, 255, 0);
		sprite->SetLocalPosition(middle);
		sprite->SetDisplayMode(DisplayMode::Center);
		sprite->SetLocalRotation(lineVec.GetAngleRadians());
		sprite->SetLocalScale(Vec2(lineVec.Length(), 2.0f));
	}
	std::cout << std::endl;

	_collidersShown = true;
}
