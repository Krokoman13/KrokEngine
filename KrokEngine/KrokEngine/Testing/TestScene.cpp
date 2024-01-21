#include "TestScene.hpp"
#include "Detector.hpp"
#include "Ball.hpp"

TestScene::TestScene() : PhysicsScene("TestScene")
{
}

void TestScene::update()
{
	if (Input::WentDown(Mouse::Button::Left))
	{
		if (_current) return;
		_current = new Ball(Input::MousePos());
		_current->rb->onTriggerEnterAction = [this](Collider* pCollider) {TriggerColliderComponent::EnterReport(this, pCollider); };
		AddChild(_current);
	}

	if (Input::WentDown(Mouse::Button::Right))
	{
		GameObject* sphere = new GameObject(Vec2(Input::MousePos()));
		Sprite* sprite = sphere->AddComponent<Sprite>(RS__BALL_PNG);
		sprite->diffuseColor = Color::Blue();
		sprite->SetDisplayMode(DisplayMode::Center);

		AddChild(sphere);
	}

	if (_current == nullptr) return;
}

void TestScene::onLoad()
{
	const float width = 1150.0f;
	const float height = width/2.0f;

	PhysicsObject* box = new PhysicsObject(PolyShape::Rectangle(Vec2(0.f, 0.f), width, height).Invert(), Vec2(1, 1));
	AddChild(box);
	box->ShowCollider();
}
