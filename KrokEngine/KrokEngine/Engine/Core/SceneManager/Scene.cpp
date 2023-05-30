#include "Scene.hpp"
#include "../../Essentials/ManagedPtr.hpp"

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

	while (_toRemove.size() > 0)
	{
		ManagedPtr<GameObject> toRemove = _toRemove.front();
		_toRemove.pop();

		if (toRemove.IsDestroyed()) continue;
		std::cout << "Removing: " << toRemove->name;
		toRemove.Destroy();
	}
}

void Scene::Close()
{
	OnClose();

	if (_reloadOnOpen) loaded = false;
}

void Scene::LateRemove(ManagedPtr<GameObject> pToRemove)
{
	_toRemove.push(pToRemove);
}

void Scene::OnClose()
{
}

const std::vector<ManagedPtr<GameObject> >& Scene::ToLoad() const
{
	return _toLoad;
}

void Scene::AddToScene(ManagedPtr<GameObject>  pGameObject)
{
	_toLoad.push_back(pGameObject);
	//_inScene.push_back(pGameObject);
	pGameObject->SetScene(this);
}
