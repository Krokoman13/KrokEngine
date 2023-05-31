#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "Transform.hpp"
#include "../Core/Math/Vec2.hpp"
#include "Component.hpp"

class Scene;

class GameObject : public Transform
{
public:
	GameObject(Vec2 pPosition, std::string pName = "GameObject");
	GameObject(std::string pName = "GameObject", float pX = 0.0f, float pY = 0.0f);
	GameObject(const GameObject& pOther) = delete;
	GameObject& operator =(const GameObject& pOther) = delete;
	virtual ~GameObject();

	std::string name;

	GameObject* GetParent() const;
	void SetParent(Transform* pParent) = delete;

	void ClearParent();

	bool HasChild(GameObject* pOther) const;
	unsigned int ChildCount() const;
	GameObject* GetChild(unsigned int i) const;

	void AddChild(GameObject * pChild);

	void RemoveChild(GameObject* pChild);

	int GetRenderLayer() const;
	bool CanRender() const;
	void SetRenderLayer(int renderLayer);

	virtual sf::Sprite* GetSprite();

	void SetScene(Scene* scene);
	Scene* GetScene() const;

	void SetActive(bool pEnabled = true);
	bool IsActive() const;

	void Update();
	void OnLoad();
	void OnEnable();
	void OnDisable();

	const std::vector<std::unique_ptr<Component>>& GetComponents() const;

	template<typename T>
	bool TryGetComponent(T*& outp)
	{
		static_assert(std::is_base_of<Component, T>::value, "T must be a derived class of Component");

		for (unsigned int i = 0; i < _components.size(); i++)
		{
			T* current = dynamic_cast<T*>(_components[i].get());

			if (current != nullptr)
			{
				outp = current;
				return true;
			}
		}

		return false;
	};

	void AddComponent(Component* pComponent);

	void LateDestroy();

protected:
	bool _canRender = false;
	int _renderLayer = -1;

	std::vector<std::unique_ptr<GameObject>> _children;
	int childIndex(GameObject* pChild);

	Scene* _scene;

	virtual void update();
	virtual void onLoad();

	void removeChild(unsigned int i);

private:
	void migrateChild(unsigned int pChildIndex, GameObject* newParent);
	void migrateChild(GameObject* pChild, GameObject* newParent);

	bool _enabled = false;

	std::vector<std::unique_ptr<Component>> _components;
};

