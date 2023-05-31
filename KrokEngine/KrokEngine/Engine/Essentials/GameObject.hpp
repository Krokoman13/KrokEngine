#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "Transform.hpp"
#include "../Core/Math/Vec2.hpp"
#include "Component.hpp"
#include "OB_SmartPointers.hpp"

class Scene;

class GameObject : public Transform
{
public:
	GameObject(Vec2 pPosition, std::string pName = "GameObject");
	GameObject(std::string pName = "GameObject", float pX = 0.0f, float pY = 0.0f);
	virtual ~GameObject();

	void ClearChildren();

	std::string name;

	GameObject* GetParent() const;
	void SetParent(Transform* pParent) = delete;

	void ClearParent();

	bool HasChild(GameObject* pOther) const;
	//const std::vector <GmObjctPtr> GetChildren() const;
	unsigned int ChildCount() const;
	borrow_ptr<GameObject> GetChild(unsigned int i) const;

	void AddChild(borrow_ptr<GameObject> pChild);
	void AddChild(GameObject* pChild);

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

	borrow_ptr<GameObject> GetBorrowPtr() const;

	template<typename T>
	bool TryGetComponent(borrow_ptr<T>& outp)
	{
		static_assert(std::is_base_of<Component, T>::value, "T must be a derived class of Component");

		for (unsigned int i = 0; i < _components.size(); i++)
		{
			Component* component = _components[i].Get();
			T* current = dynamic_cast<T*>(component);

			if (current != nullptr)
			{
				outp = _components[i].TryCast<T>();
				return true;
			}
		}

		return false;
	};

	void AddComponent(Component* pComponent);

	void Delete();

protected:
	bool _canRender = false;
	int _renderLayer = -1;

	std::vector<borrow_ptr<GameObject>> _children;

	Scene* _scene;

	virtual void update();
	virtual void onLoad();

private:
	void setParent(GameObject* pParent);
	bool _enabled = false;

	owning_ptr<GameObject> _ptr;
	std::vector<owning_ptr<Component>> _components;
};

