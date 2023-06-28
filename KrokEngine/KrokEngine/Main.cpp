#include "Engine/KrokEngine.hpp"
#include "Testing/TestScene.hpp"
#include "Testing/PolyshapeCollisionTester.hpp"
#include "Testing/GravityTest.hpp"
#include <vector>

int main()
{
	ImageGameObject::ASSET_PATH = "Assets/";
	UIElement::ASSET_PATH = "Assets/UI/";
	UIElement::DEFAULT_FONT.loadFromFile("arial.ttf");

	Game myGame("Demo", 1280, 720, 120);
	myGame.AddScene(new TestScene());
	//myGame.GoToScene("TestScene");
	myGame.AddScene(new PolyshapeCollisionTester());
	//myGame.GoToScene("PolyshapeCollisionTester");
	myGame.AddScene(new GravityTest());
	myGame.GoToScene("GravityTest");

	myGame.Run();
	return 0;
}
