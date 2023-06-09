#pragma once
#include "../../Essentials/GameObject.hpp"
#include "../UI/UI.hpp"

class SceneManager;

class Scene : public GameObject
{
public:
	Scene(std::string Name = "Scene", bool reloadOnOpen = false);
	virtual ~Scene();

	bool loaded = false;
	unsigned int identifier = 0;

	UI* ui;

	void Load();
	void Close();

	SceneManager* sceneManager;

	virtual void OnClose();

protected:
	bool _reloadOnOpen;
	void loadChildren(GameObject* gameObject);
};

