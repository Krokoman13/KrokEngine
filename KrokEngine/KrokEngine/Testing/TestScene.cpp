#include "TestScene.hpp"
#include "Detector.hpp"
#include "Ball.hpp"

TestScene::TestScene() : PhysicsScene("TestScene")
{
}

void TestScene::update()
{
	if (Input::WentDown(sf::Mouse::Left))
	{
		if (_current) return;
		_current = new Ball(Input::mousePosition);
		AddChild(_current);
	}

	if (Input::WentDown(sf::Mouse::Right))
	{
		AddChild(new Detector(Input::mousePosition));
	}

	if (_current == nullptr) return;
}

void TestScene::onLoad()
{
	//AddChild(new MouseFollowingObject());
	AddChild(new ImageGameObject("PoolTableFrame.png", Vec2(), 0));

	const float width = 1150.0f;
	const float height = width/2.0f;

	PhysicsObject* box = new PhysicsObject(PolyShape::Rectangle(Vec2(64.0f, 64.0f), width, height).Invert(), Vec2(0, 1.5f));
	AddChild(box);
	box->ShowCollider();
}
