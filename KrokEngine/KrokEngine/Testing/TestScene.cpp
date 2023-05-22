#include "TestScene.hpp"
#include "MovingObject.hpp"
#include "MouseFollowingObject.hpp"
#include "MouseFollowingBehaviour.hpp"
#include "PhysicsLine.hpp"

TestScene::TestScene() : Scene("TestScene")
{
}

void TestScene::onLoad()
{
	AddChild(new MouseFollowingObject());
	PhysicsLine* line = new PhysicsLine(Vec2(50.0f, 400.0f), Vec2(1000.0f, 700.0f));
	//line->AddComponent(new MouseFollowingBehaviour());
	AddChild(line);
	

	//MovingObject* movingObject = new MovingObject(0, 0);
	//movingObject->SetLocalScale(0.5f);
	//mouseObject->AddChild(movingObject);

	//ImageGameObject* imgObject = new ImageGameObject("Smiley.jpg", 500, 250);
	//imgObject->SetLocalScale(0.1f);
	//imgObject->centered = true;
	//movingObject->AddChild(imgObject);
}
