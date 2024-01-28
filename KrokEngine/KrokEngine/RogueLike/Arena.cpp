#include "Arena.hpp"
#include "Barry.hpp"
#include "Chest.hpp"

void Arena::onLoad()
{
	float scale = 4.f;

	sceneManager->GetGame()->GetCamera().SetScale(scale);

	Sprite::defaultMagFilterParam = GL_NEAREST;
	Sprite::defaultMinFilterParam = GL_NEAREST;

	AddChild(new Barry(Vec2(50, 50)));
	AddChild(new Chest(Vec2(100, 100)));

	GameObject* backgroundObject = new GameObject(Vec2(-5, -5));
	AddChild(backgroundObject);
	Sprite* backgroundSprite = backgroundObject->AddComponent<Sprite>(RS__LEVELONEBACKGROUND_PNG);
	backgroundSprite->SetDisplayMode(DisplayMode::TopLeft);
	backgroundSprite->SetRenderLayer(-1);

	const float width = 1280.f / scale - 2;
	const float height = 720.f / scale - 5;

	PhysicsObject* box = new PhysicsObject(PolyShape::Rectangle(Vec2(1, 5.f), width, height).Invert(), Vec2(0.f, 0.f));
	box->collider->bounciness = 0.f;

	AddChild(box);
}
