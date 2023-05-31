#include "TestScene.hpp"
#include "MovingObject.hpp"
#include "MouseFollowingObject.hpp"
#include "MouseFollowingBehaviour.hpp"
#include "PhysicsLine.hpp"
#include "Ball.hpp"

TestScene::TestScene() : PhysicsScene("TestScene")
{
}

void TestScene::update()
{
	if (Input::WentUp(sf::Mouse::Left))
	{
		Ball* ball = new Ball(Input::mousePosition);
		//ball->AddComponent(new MouseFollowingBehaviour());
		AddChild(ball);
	}

	if (Input::WentDown(sf::Mouse::Right))
	{
		ImageGameObject* sphere = new ImageGameObject("Debug/Redcircle.png", Vec2(Input::mousePosition));
		sphere->centered = true;
		sphere->AddComponent(new ColliderComponent(new CircleCollider(sphere->GetWidth() / 2.0f)));
		AddChild(sphere);
	}
}

void TestScene::onLoad()
{
	PhysicsLine* line = new PhysicsLine(Vec2(50.0f, 400.0f), Vec2(500.0f, 700.0f));
	AddChild(line);

	line = new PhysicsLine(Vec2(500.0f, 700.0f), Vec2(1000.0f, 400.0f));
	AddChild(line);
}
