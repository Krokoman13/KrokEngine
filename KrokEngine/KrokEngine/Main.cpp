#include "Engine/KrokEngine.hpp"

int main()
{
	ImageGameObject::ASSET_PATH = "Assets/";
	UIElement::ASSET_PATH = "Assets/UI/";
	UIElement::DEFAULT_FONT.loadFromFile("arial.ttf");

	Game myGame("Demo", 1280, 720, 60);

	myGame.Run();

	return 0;
}
