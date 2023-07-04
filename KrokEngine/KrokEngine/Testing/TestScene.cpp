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
	//if (Input::WentDown(sf::Mouse::Left))
	//{
	//	std::cout << Input::mousePosition << '\n';
	//}
	//return;
	if (Input::WentDown(sf::Mouse::Left))
	{
		_current = new Ball(Input::mousePosition);
		//ball->AddComponent(new MouseFollowingBehaviour());
		AddChild(_current);
	}

	if (Input::WentDown(sf::Mouse::Right))
	{
		ImageGameObject* sphere = new ImageGameObject("Debug/Redcircle.png", Vec2(Input::mousePosition));
		sphere->centered = true;
		sphere->AddComponent(new ColliderComponent(new CircleCollider(sphere->GetWidth() / 2.0f)));
		AddChild(sphere);
	}

	if (_current == nullptr) return;

	_current->SetGlobalPosition(Input::mousePosition);

	if (Input::WentUp(sf::Mouse::Left))
	{
		Vec2 direction = Input::mousePosition - Input::previousMousePosition;
		direction *= (1 / sceneManager->GetGame()->deltaSeconds);
		direction /= 100.0f;

		//std::cout << direction << '\n';

		_current->rb->velocity =  direction;
		_current = nullptr;
	}
}

void TestScene::onLoad()
{
	AddChild(new ImageGameObject("PoolTableFrame.png", Vec2(), 0));

	const float width = 1150.0f;
	const float height = width/2.0f;

	PhysicsObject* box = new PhysicsObject(PolyShape::Rectangle(Vec2(64.0f, 64.0f), width, height).Invert(), Vec2(0, 1.5f));
	AddChild(box);
	box->ShowCollider();
}
