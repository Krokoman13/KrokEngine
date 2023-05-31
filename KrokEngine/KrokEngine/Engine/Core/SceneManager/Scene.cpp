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
		if (_parentLess.front())
		{
			std::cout << "Removing: " << _parentLess.front()->name;
			_parentLess.front().destroy();
		}

		_parentLess.pop();
	}
}

void Scene::Close()
{
	OnClose();

	if (_reloadOnOpen) loaded = false;
}

void Scene::Parentless(owning_ptr<GameObject>&& pToRemove)
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
