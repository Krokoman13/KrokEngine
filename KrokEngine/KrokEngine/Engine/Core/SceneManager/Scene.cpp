#include "Scene.hpp"
#include "../../Essentials/GmObjctPtr.hpp"

Scene::Scene(std::string Name, bool reloadOnOpen) : GameObject(name)
{
	ui = new UI();
	name = Name;
	_reloadOnOpen = reloadOnOpen;
}

Scene::~Scene()
{
	ClearChildren();
	delete ui;
}

void Scene::Load()
{
	ClearChildren();
	ui->ClearUi();

	OnLoad();

	SetScene(this);

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
}

void Scene::Close()
{
	OnClose();

	if (_reloadOnOpen) loaded = false;
}

void Scene::OnClose()
{
}

const std::vector<GmObjctPtr>& Scene::ToLoad() const
{
	return _toLoad;
}

void Scene::AddToScene(GmObjctPtr pGameObject)
{
	_toLoad.push_back(pGameObject);
	//_inScene.push_back(pGameObject);
	pGameObject->SetScene(this);
}
