#pragma once
#include "../../Essentials/GameObject.hpp"

class SceneManager;

class Scene : public GameObject
{
public:
	Scene(std::string pName);
	virtual ~Scene() override
	{
		destroyChildrenImmediatly();
	}

	unsigned int identifier = 0;

	virtual void Load();

	void AddToScene(GameObject*  pGmObject);
	virtual void HandleObjectsInScene();

	void Close();
	virtual void clearScene();

	void Parentless(std::unique_ptr<GameObject>& pToRemove);

	SceneManager* sceneManager;

	virtual void OnClose();

	const std::vector<GameObject*>& ToLoad() const;
	const std::vector<std::unique_ptr<GameObject>>& ToDestroy() const;

private:
	std::vector<GameObject*> _toLoad;
	std::vector<std::unique_ptr<GameObject>> _toDestroy;
};

