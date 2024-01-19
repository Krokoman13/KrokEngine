#pragma once
#include "../../Essentials/GameObject.hpp"

#include "../Graphics/ResourceManager/ResourceCache/SelfRegResourceCache.hpp"
#include "../Graphics/Core/Texture/Texture.hpp"

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
	SelfRegResourceCache<Texture, std::string> m_textureCache;
};

