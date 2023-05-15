#include "Scene.hpp"
#include "../../Essentials/GmObjctPtr.hpp"

Scene::Scene(std::string Name, bool reloadOnOpen) : GameObject(0, 0, "Scene")
{
	this->ui = new UI();
	this->name = Name;
	this->_reloadOnOpen = reloadOnOpen;
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
	load(this);
	loaded = true;
}

void Scene::Close()
{
	OnClose();

	if (_reloadOnOpen) loaded = false;
}

void Scene::OnClose()
{
}

void Scene::load(GameObject* gmObject)
{
	for (GmObjctPtr child : gmObject->GetChildren())
	{
		child->SetScene(this);
		child->OnLoad();
		load(child);
	}
}
