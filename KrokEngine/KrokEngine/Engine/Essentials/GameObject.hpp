#pragma once
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
	GameObject(const Vec2& pPosition, const std::string& pName = "GameObject");
	GameObject(const std::string& pName = "GameObject", const float pX = 0.0f, const float pY = 0.0f);
	GameObject(const GameObject& pOther) = delete;
	GameObject& operator =(const GameObject& pOther) = delete;
	virtual ~GameObject();

	std::string name;

	GameObject* GetParent() const;
	void SetParent(Transform* pParent) = delete;

	void ClearParent();

	bool HasChild(GameObject* pOther) const;
	unsigned int ChildCount() const;
	GameObject* GetChild(const unsigned int i) const;

	void AddChild(GameObject * pChild);

	void RemoveChild(GameObject* pChild);

	int GetRenderLayer() const;
	void SetRenderLayer(int pRenderlayer);

	void SetScene(Scene* scene);
	Scene* GetScene() const;

	Matrix3 MatrixInScreen();

	void SetActive(const bool pEnabled = true);
	bool IsActive() const;

	void Update();
	void OnLoad();
	void OnEnable();
	void OnDisable();

	const std::vector<std::unique_ptr<Component>>& Components() const;

	template<typename T>
	std::vector<T*> GetComponents()
	{
		static_assert(std::is_base_of<Component, T>::value, "T must be a derived class of Component");

		std::vector<T*> outp;

		for (const std::unique_ptr<Component>& component : _components)
		{
			T* current = dynamic_cast<T*>(component.get());
			if (!current) continue;

			outp.push_back(current);
		}

		return outp;
	}

	template<typename T>
	bool TryGetComponent(T*& outp)
	{
		static_assert(std::is_base_of<Component, T>::value, "T must be a derived class of Component");

		for (const std::unique_ptr<Component>& component : _components)
		{
			T* current = dynamic_cast<T*>(component.get());
			if (!current) continue;

			outp = current;
			return true;
		}

		return false;
	};

	template<typename T, typename... Args>
	T* AddComponent(Args... args)
	{
		static_assert(std::is_base_of<Component, T>::value, "T must be a derived class of Component");

		std::unique_ptr<T> component = std::make_unique<T>(args...);
		component->SetGameObject(this);
		
		T* outp = component.get();
		_components.push_back(std::move(component));

		return outp;
	}

	void LateDestroy();

protected:
	bool _canRender = false;
	int _renderLayer = -1;

	std::vector<std::unique_ptr<GameObject>> _children;
	int childIndex(GameObject* pChild);

	Scene* _scene;

	virtual void update();	//Meant to be overriden
	virtual void onLoad();	//Meant to be overriden

	void removeChild(const unsigned int i);
	void destroyChildrenImmediatly();

private:
	void migrateChild(unsigned int pChildIndex, GameObject* newParent);
	void migrateChild(GameObject* pChild, GameObject* newParent);

	bool _enabled = false;

	std::vector<std::unique_ptr<Component>> _components;
};

