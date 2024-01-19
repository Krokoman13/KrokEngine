#include "Engine/KrokEngine.hpp"
#include "Testing/TestScene.hpp"

int main()
{
	//PathManager::ResetPaths();
	PathManager::MapPaths();

	Game myGame("Demo", 1280, 720, 120);
	myGame.devControls = true;

	myGame.AddScene(new TestScene());
	GameObject* image = new GameObject();
	Sprite* sprite = image->AddComponent<Sprite>(RS__BRICKS_JPG);
	sprite->SetRenderLayer(-1);
	sprite->SetLocalScale(100);
	image->SetLocalPosition(100, 100);
	myGame.GetCurrentScene()->AddChild(image);

	myGame.Run();
	return 0;
}
