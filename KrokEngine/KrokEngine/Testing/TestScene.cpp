#include "TestScene.hpp"
#include "MovingObject.hpp"

TestScene::TestScene() : Scene("TestScene")
{
}

void TestScene::OnLoad()
{
	MovingObject* movingObject = new MovingObject(1280 / 2, 720 / 2);
	movingObject->SetLocalScale(0.5f);
	AddChild(movingObject);

	ImageGameObject* imgObject = new ImageGameObject("Smiley.jpg", 500, 250);
	imgObject->SetLocalScale(0.1f);
	imgObject->centered = true;
	movingObject->AddChild(imgObject);
}
