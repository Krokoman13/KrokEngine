#pragma once
#include "../../Essentials/GameObject.hpp"
#include "../UI/UI.hpp"

class SceneManager;

class Scene : public GameObject
{
public:
	Scene(std::string pName, bool pReloadOnOpen = false);
	virtual ~Scene();

	bool loaded = false;
	unsigned int identifier = 0;

	UI* ui;

	virtual void Load();
	void AddToScene(GameObject*  pGmObject);
	virtual void HandleObjectsInScene();
	void Close();

	void Parentless(std::unique_ptr<GameObject>& pToRemove);

	SceneManager* sceneManager;

	virtual void OnClose();

	const std::vector<GameObject*>& ToLoad() const;
	const std::vector<std::unique_ptr<GameObject>>& ToDestroy() const;

protected:
	bool _reloadOnOpen;

private:
	std::vector<GameObject*> _toLoad;
	std::vector<std::unique_ptr<GameObject>> _toDestroy;
};

