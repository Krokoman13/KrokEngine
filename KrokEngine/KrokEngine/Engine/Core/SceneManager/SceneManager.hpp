#pragma once
#include <vector>
#include <string>

class Scene;
class Game;

class SceneManager
{
public:
	SceneManager(Game* pGame = nullptr);
	SceneManager(Scene* startScene, Game* pGame = nullptr);
	virtual ~SceneManager();

public:
	Scene* GetCurrentScene();

	Scene* GetScene(Scene* scene);
	Scene* GetScene(const std::string& pSceneName);
	Scene* GetScene(const unsigned int pSceneIdentifier);

	void GoToScene(Scene* scene);
	void GoToScene(const std::string& pSceneName);
	void GoToScene(const unsigned int pSceneIdentifier);

	void GoToNextScene();
	void GoToPreviousScene();

	void AddScene(Scene* scene);
	
	void ReloadCurrentScene();

	Game* GetGame();

	bool IsNewScene() { return _sceneIsNew; };

protected:
	void closeScene(Scene* scene);
	void openScene(Scene* scene);

	void clearAllScenes();

	bool _sceneIsNew = true;

private:
	unsigned int findIdentifier(std::string name);
	std::vector<Scene*> _scenes = {};
	Scene* _currentScene;
	Game* _game;
};

