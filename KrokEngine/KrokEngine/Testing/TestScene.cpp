#include "TestScene.hpp"
#include "MovingObject.hpp"
#include "MouseFollowingObject.hpp"

TestScene::TestScene() : Scene("TestScene")
{
}

void TestScene::OnLoad()
{
	MouseFollowingObject* mouseObject = new MouseFollowingObject();
	AddChild(mouseObject);

	//MovingObject* movingObject = new MovingObject(0, 0);
	//movingObject->SetLocalScale(0.5f);
	//mouseObject->AddChild(movingObject);

	//ImageGameObject* imgObject = new ImageGameObject("Smiley.jpg", 500, 250);
	//imgObject->SetLocalScale(0.1f);
	//imgObject->centered = true;
	//movingObject->AddChild(imgObject);
}
