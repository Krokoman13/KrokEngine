#include "Engine/KrokEngine.hpp"
#include "Testing/TestScene.hpp"

#include "Testing/UpdateComponent.hpp"
#include <stdlib.h>

int main()
{
	//PathManager::ResetPaths();
	PathManager::MapPaths();

	Game myGame("Demo", 1280, 720, 120);
	myGame.devControls = true;

	myGame.AddScene(new TestScene());

	{
		GameObject* image = new GameObject();
		Sprite* sprite = image->AddComponent<Sprite>(RS__BRICKS_JPG);
		sprite->SetRenderLayer(0);
		sprite->SetLocalScale(100);
		image->SetLocalPosition(100, 100);
		myGame.GetCurrentScene()->AddChild(image);
	}

	{
		GameObject* image = new GameObject();
		Sprite* sprite = image->AddComponent<Sprite>(RS__BRICKS_JPG);
		sprite->SetRenderLayer(1);
		sprite->diffuseColor = Color(0, 0, 255);
		sprite->SetLocalScale(100);
		image->SetLocalPosition(150, 150);
		myGame.GetCurrentScene()->AddChild(image);
	}

	{
		GameObject* image = new GameObject();
		Sprite* sprite = image->AddComponent<Sprite>(RS__BRICKS_JPG);
		sprite->SetRenderLayer(3);
		sprite->diffuseColor = Color(255, 0, 0);
		sprite->SetLocalScale(100);
		image->SetLocalPosition(200, 200);
		myGame.GetCurrentScene()->AddChild(image);
	}

	{
		GameObject* image = new GameObject();
		Sprite* sprite = image->AddComponent<Sprite>(RS__BRICKS_JPG);
		sprite->SetRenderLayer(2);
		sprite->diffuseColor = Color(0, 255, 0);
		sprite->SetLocalScale(100);
		image->SetLocalPosition(250, 250);
		myGame.GetCurrentScene()->AddChild(image);
	}

	myGame.Run();
	return 0;
}
