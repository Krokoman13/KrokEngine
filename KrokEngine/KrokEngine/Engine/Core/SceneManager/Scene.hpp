#pragma once
#include "../../Essentials/GameObject.hpp"
#include "../UI/UI.hpp"
#include <queue>

class SceneManager;

class Scene : public GameObject
{
public:
	Scene(std::string pName, bool pReloadOnOpen = false);
	virtual ~Scene();

	bool loaded = false;
	unsigned int identifier = 0;

	UI* ui;

	void Load();
	void AddToScene(ManagedPtr<GameObject>  pGmObject);
	void HandleObjectsInScene();
	void Close();

	void LateRemove(ManagedPtr<GameObject> pToRemove);

	SceneManager* sceneManager;

	virtual void OnClose();

	const std::vector<ManagedPtr<GameObject> >& ToLoad() const;

protected:
	bool _reloadOnOpen;

private:
	std::vector<ManagedPtr<GameObject>> _toLoad;
	std::queue<ManagedPtr<GameObject>> _toRemove;
};

