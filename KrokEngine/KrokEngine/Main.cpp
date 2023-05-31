#include "Engine/KrokEngine.hpp"
#include "Testing/TestScene.hpp"
#include <vector>

int main()
{
	ImageGameObject::ASSET_PATH = "Assets/";
	UIElement::ASSET_PATH = "Assets/UI/";
	UIElement::DEFAULT_FONT.loadFromFile("arial.ttf");

	Game myGame("Demo", 1280, 720, 120);
	myGame.AddScene(new TestScene());
	myGame.GoToScene("TestScene");

	myGame.Run();

	return 0;
}
