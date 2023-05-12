#include "Engine/KrokEngine.hpp"
#include "Testing/MovingObject.hpp"
#include "Engine/Core/Math/Matrix.hpp"
#include <iostream>

int main()
{
	ImageGameObject::ASSET_PATH = "Assets/";
	UIElement::ASSET_PATH = "Assets/UI/";
	UIElement::DEFAULT_FONT.loadFromFile("arial.ttf");

	Game myGame("Demo", 1280, 720, 60);

	MovingObject* movingObject = new MovingObject(1280/2, 720/2);
	movingObject->SetLocalScale(0.5f);
	myGame.GetCurrentScene()->AddChild(movingObject);

	ImageGameObject* imgObject = new ImageGameObject("Smiley.jpg", 500, 250);
	imgObject->SetLocalScale(0.1f);
	imgObject->centered = true;
	movingObject->AddChild(imgObject);
	//myGame.GetCurrentScene()->AddChild(imgObject);

	myGame.Run();
	

	return 0;
}
