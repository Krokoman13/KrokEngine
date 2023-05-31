#include "Scene.hpp"
#include "SceneManager.hpp"

Scene::Scene(std::string Name, bool reloadOnOpen) : GameObject(name)
{
	ui = new UI();
	name = Name;
	_reloadOnOpen = reloadOnOpen;
	_scene = this;
}

Scene::~Scene()
{
	delete ui;
}

void Scene::Load()
{
	while (!_children.empty())
	{
		_children.back()->LateDestroy();
	}
	ui->ClearUi();

	OnLoad();

	loaded = true;
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

	if (_reloadOnOpen) loaded = false;
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
	pGameObject->SetScene(this);
}
