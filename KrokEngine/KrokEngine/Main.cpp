#include "Engine/KrokEngine.hpp"
#include "Testing/TestScene.hpp"

#include "Testing/UpdateComponent.hpp"
#include "Testing/Button.hpp"
#include <stdlib.h>

int main()
{
	//PathManager::ResetPaths();
	PathManager::MapPaths();

	Game myGame("Demo", 1280, 720, 120);
	myGame.devControls = true;

	myGame.AddScene(new Scene("Test"));

	{
		ButtonObject* button = new ButtonObject(RS__BUTTON_PNG, RS__BUTTON_2_PNG, Rectangle(200, 100));
		myGame.GetCurrentScene()->AddChild(button);
		button->SetLocalPosition(500, 500);
		button->SetFunction([]() { std::cout << "Click1!"; });
	}

	{
		ButtonObject* button = new ButtonObject(RS__BUTTON_PNG, RS__BUTTON_2_PNG, Rectangle(200, 100));
		myGame.GetCurrentScene()->AddChild(button);
		button->SetLocalPosition(550, 550);
	}

	{
		ButtonObject* button = new ButtonObject(RS__BUTTON_PNG, RS__BUTTON_2_PNG, Rectangle(200, 100));
		myGame.GetCurrentScene()->AddChild(button);
		button->SetLocalPosition(500, 550);
	}

	{
		ButtonObject* button = new ButtonObject(RS__BUTTON_PNG, RS__BUTTON_2_PNG, Rectangle(200, 100));
		myGame.GetCurrentScene()->AddChild(button);
		button->SetLocalPosition(550, 500);
	}

	myGame.Run();
	return 0;
}
