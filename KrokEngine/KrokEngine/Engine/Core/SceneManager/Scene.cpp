#include "Scene.hpp"
#include "../../Essentials/OB_SmartPointers.hpp"

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
		borrow_ptr<GameObject> toRemove = _parentLess.front();
		_parentLess.pop();

		if (!toRemove || toRemove->GetParent() != nullptr) continue;

		std::cout << "Removing: " << toRemove->name;
		toRemove->Delete();
	}
}

void Scene::Close()
{
	OnClose();

	if (_reloadOnOpen) loaded = false;
}

void Scene::Parentless(borrow_ptr<GameObject> pToRemove)
{
	_parentLess.push(pToRemove);
}

void Scene::OnClose()
{
}

const std::vector<borrow_ptr<GameObject> >& Scene::ToLoad() const
{
	return _toLoad;
}

void Scene::AddToScene(borrow_ptr<GameObject>  pGameObject)
{
	_toLoad.push_back(pGameObject);
	//_inScene.push_back(pGameObject);
	pGameObject->SetScene(this);
}
