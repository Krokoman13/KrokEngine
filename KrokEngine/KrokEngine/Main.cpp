#include "Engine/KrokEngine.hpp"
#include "RogueLike/Arena.hpp"

int main()
{
	//PathManager::ResetPaths();
	PathManager::MapPaths();

	Game myGame("Demo", 1280, 720, 120);
	myGame.devControls = true;
	myGame.AddScene(new Arena());

	myGame.Run();
	return 0;
}
