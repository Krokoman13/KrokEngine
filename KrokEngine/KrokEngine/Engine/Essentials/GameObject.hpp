#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "Transform.hpp"
#include "../Core/Math/Vec2.hpp"
#include "Component.hpp"
#include "GmObjctPtr.hpp"

class Scene;

class GameObject : public Transform
{
public:
	GameObject(Vec2 pPosition, std::string pName = "GameObject");
	GameObject(std::string pName = "GameObject", float pX = 0.0f, float pY = 0.0f);
	~GameObject();

	void ClearChildren();

	std::string name;

	GameObject* GetParent() const;
	void SetParent(Transform* pParent) = delete;
	void SetParent(GameObject* pParent);

	void ClearParent();

	bool HasChild(GmObjctPtr pOther) const;
	//const std::vector <GmObjctPtr> GetChildren() const;
	unsigned int ChildCount() const;
	GmObjctPtr GetChild(unsigned int i) const;

	void AddChild(GmObjctPtr pChild);
	GmObjctPtr AddChild(GameObject* pChild);
	void RemoveChild(unsigned int i);
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

	template<typename T>
	bool TryGetComponent(T*& outp)
	{
		static_assert(std::is_base_of<Component, T>::value, "T must be a derived class of Component");

		for (unsigned int i = 0; i < _components.size(); i++)
		{
			Component* component = _components[i].get();

			T* current = dynamic_cast<T*>(component);

			if (current != nullptr)
			{
				outp = current;
				return true;
			}
		}

		return false;
	};

	void AddComponent(Component* pComponent);

	void SetPtr(GmObjctPtr pPtr);

	void Delete();

	operator GmObjctPtr();

protected:
	bool _canRender = false;
	int _renderLayer = -1;

	//GameObject* _parent = nullptr;
	std::vector <GmObjctPtr> _children;

	int getChildIndex();
	Scene* _scene;

	virtual void update();
	virtual void onLoad();

private:
	void setParent(GameObject* pParent);
	bool _enabled = false;

	std::vector<std::unique_ptr<Component>> _components;

	GmObjctPtr _ptr;
};

