#include "Arena.hpp"
#include "Barry.hpp"
#include "Pillar.hpp"

void Arena::onLoad()
{
	AddChild(new Barry(Vec2(500, 500)));
	AddChild(new Pillar(Vec2(500, 400)));

	GameObject* backgroundObject = new GameObject();
	AddChild(backgroundObject);
	Sprite* backgroundSprite = backgroundObject->AddComponent<Sprite>(RS__LEVELONEBACKGROUND_PNG);
	backgroundSprite->SetDisplayMode(DisplayMode::TopLeft);
	backgroundSprite->SetRenderLayer(-1);

	const float width = 1277.f;
	const float height = 600.f;
	PhysicsObject* box = new PhysicsObject(PolyShape::Rectangle(Vec2(0.f, 115.f), width, height).Invert(), Vec2(1, 1));
	box->collider->bounciness = 0.f;
	AddChild(box);
	box->ShowCollider();
}
