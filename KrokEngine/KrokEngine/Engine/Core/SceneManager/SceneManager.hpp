#pragma once
#include "Scene.hpp"
#include <vector>
#include <string>

class Game;

class SceneManager
{
public:
	SceneManager(Game* pGame = nullptr);
	SceneManager(Scene* startScene, Game* pGame = nullptr);
	~SceneManager();

	Scene* GetCurrentScene();

	Scene* GetScene(Scene* scene);
	Scene* GetScene(std::string SceneName);
	Scene* GetScene(int SceneIdentifier);

	void GoToScene(Scene* scene);
	void GoToScene(std::string SceneName);
	void GoToScene(int ScineIdentifier);

	void AddScene(Scene* scene);
	
	void reloadCurrentScene();

	Game* GetGame();

protected:
	void closeScene(Scene* scene);
	void openScene(Scene* scene);

private:
	unsigned int findIdentifier(std::string name);
	std::vector<Scene*> _scenes = {};
	Scene* _currentScene;
	Game* _game;
};

