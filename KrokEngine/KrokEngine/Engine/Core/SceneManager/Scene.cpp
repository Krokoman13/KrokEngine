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

	while (_parentLess.size() > 0)
	{
		GameObject* currnent = _parentLess.back();
		_parentLess.pop_back();

		if (currnent == nullptr) continue;
		if (currnent->GetParent() != nullptr) continue;

		std::cout << "Removing parentless GameObject: " << currnent->name << '\n';
		delete currnent;
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

void Scene::IsParentless(GameObject* pGameObject)
{
	if (pGameObject == nullptr) throw std::invalid_argument("gameObject is a nullpointer");

	_parentLess.push_back(pGameObject);
}
