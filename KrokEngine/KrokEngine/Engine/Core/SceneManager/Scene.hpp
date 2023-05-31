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
	void AddToScene(borrow_ptr<GameObject>  pGmObject);
	void HandleObjectsInScene();
	void Close();

	void Parentless(owning_ptr<GameObject>&& pToRemove);

	SceneManager* sceneManager;

	virtual void OnClose();

	const std::vector<borrow_ptr<GameObject> >& ToLoad() const;

protected:
	bool _reloadOnOpen;

private:
	std::vector<borrow_ptr<GameObject>> _toLoad;
	std::queue<owning_ptr<GameObject>> _parentLess;
};

