#pragma once
#include "../../Essentials/GameObject.hpp"
#include "../UI/UI.hpp"
#include <queue>

class SceneManager;

class Scene : public GameObject
{
public:
	Scene(std::string pName, bool reloadOnOpen = false);
	virtual ~Scene();

	bool loaded = false;
	unsigned int identifier = 0;

	UI* ui;

	void Load();
	void AddToScene(GmObjctPtr gmObject);
	void HandleObjectsInScene();
	void Close();

	SceneManager* sceneManager;

	virtual void OnClose();

	const std::vector<GmObjctPtr>& ToLoad() const;

protected:
	bool _reloadOnOpen;

private:
	std::vector<GmObjctPtr> _toLoad;
};

