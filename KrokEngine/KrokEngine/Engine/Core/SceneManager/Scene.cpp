#include "Scene.hpp"
#include "SceneManager.hpp"

#include "../Graphics/ResourceManager/ResourceManager.hpp"

Scene::Scene(std::string pName) : GameObject(pName), sceneManager(nullptr), m_textureCache()
{
	name = pName;
	_scene = this;
}

void Scene::Load()
{
	ResourceManager::pTexureCache = &m_textureCache;

	OnLoad();
}

void Scene::HandleObjectsInScene()
{
	unsigned int i = 0;

	while (i < _toLoad.size())
	{
		if (_toLoad[i]->IsActive())
		{
			_toLoad.erase(_toLoad.begin() + i);
			continue;
		}

		i++;
	}

	while (_toDestroy.size() > 0)
	{
		_toDestroy.pop_back();
	}
}

void Scene::Close()
{
	OnClose();

	m_textureCache.Clear();
	clearScene();
}

void Scene::clearScene()
{
	destroyChildrenImmediatly();
	_toDestroy.clear();
	_toLoad.clear();
}

void Scene::Parentless(std::unique_ptr<GameObject>& pToRemove)
{
	_toDestroy.push_back(std::move(pToRemove));
}

void Scene::OnClose()
{
}

const std::vector<GameObject*>& Scene::ToLoad() const
{
	return _toLoad;
}

const std::vector<std::unique_ptr<GameObject>>& Scene::ToDestroy() const
{
	return _toDestroy;
}

void Scene::AddToScene(GameObject* pGameObject)
{
	_toLoad.push_back(pGameObject);
}
