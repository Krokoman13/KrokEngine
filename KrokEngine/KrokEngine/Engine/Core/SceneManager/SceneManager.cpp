#include "SceneManager.hpp"
#include "../../Essentials/Game.hpp"

SceneManager::SceneManager(Game* game)
{
	_game = game;
	_currentScene = nullptr;
}

SceneManager::SceneManager(Scene* startScene, Game* game) : SceneManager(game)
{
	_scenes.push_back(startScene);
	openScene(startScene);
}

SceneManager::~SceneManager()
{
	for (Scene* scene : _scenes)
	{
		delete scene;
	}

	_scenes.clear();
}

Scene* SceneManager::GetCurrentScene()
{
	if (_currentScene == nullptr)
	{
		_currentScene = _scenes[0];
	}

	return _currentScene;
}

Scene* SceneManager::GetScene(Scene* scene)
{
	return GetScene(scene->identifier);
}

Scene* SceneManager::GetScene(const std::string& pSceneName)
{
	return GetScene(findIdentifier(pSceneName));
}

Scene* SceneManager::GetScene(unsigned int pSceneIdentifier)
{
	if (pSceneIdentifier >= (unsigned int)_scenes.size()) return nullptr;
	return _scenes[pSceneIdentifier];
}

void SceneManager::GoToScene(Scene* scene)
{
	GoToScene(scene->identifier);
}

void SceneManager::GoToScene(const std::string& pSceneName)
{
	GoToScene(findIdentifier(pSceneName));
}

void SceneManager::GoToScene(unsigned int pSceneIdentifier)
{
	Scene* nextScene = GetScene(pSceneIdentifier);
	if (!nextScene)
	{
		std::cout << "Tried to go to scene: " << pSceneIdentifier << " but it does not exist.";
		return;
	}
	if(_currentScene == nextScene) return;

	closeScene(_currentScene);
	_currentScene = nextScene;
	openScene(_currentScene);
}

void SceneManager::GoToNextScene()
{
	if (!_currentScene) return;
	GoToScene(_currentScene->identifier + 1);
}

void SceneManager::GoToPreviousScene()
{
	if (!_currentScene) return;
	GoToScene(_currentScene->identifier - 1);
}

void SceneManager::AddScene(Scene* pSCene)
{
	pSCene->sceneManager = this;

	if (_currentScene == nullptr)
	{
		if (_scenes.size() > 0) throw std::logic_error("It should not be possible that there are scenes, but not an active scene");
		_scenes.push_back(pSCene);
		openScene(pSCene);
		return;
	}

	if (pSCene->identifier == _scenes.size())
	{
		_scenes.push_back(pSCene);
		return;
	}

	if (pSCene->identifier > _scenes.size())
	{
		_scenes.push_back(nullptr);
		AddScene(pSCene);
		return;
	}

	if (_scenes[pSCene->identifier] == nullptr)
	{
		_scenes[pSCene->identifier] = pSCene;
		return;
	}

	pSCene->identifier++;
	AddScene(pSCene);
}

void SceneManager::ReloadCurrentScene()
{
	GetCurrentScene()->Close();
	GetCurrentScene()->Load();
}

Game* SceneManager::GetGame()
{
	return _game;
}

void SceneManager::closeScene(Scene* scene)
{
	std::cout << "Closing scene: " << scene->name << '\n';
	scene->Close();
	_currentScene = nullptr;
}

void SceneManager::openScene(Scene* scene)
{
	std::cout << "Opening scene: " << scene->name << '\n';

		scene->Load();
		std::cout << scene->name << " loaded\n";

	_currentScene = scene;
}

unsigned int SceneManager::findIdentifier(std::string name)
{
	for (Scene* scene : _scenes)
	{
		if (scene == nullptr) continue;

		if (scene->name == name) return scene->identifier;
	}

	return 0;
}
