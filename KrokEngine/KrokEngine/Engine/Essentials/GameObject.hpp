#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "Transform.hpp"

struct Vec2;
class GmObjctPtr;
class Scene;

class GameObject : public Transform
{
public:
	GameObject(Vec2 pPosition, std::string pName = "GameObject");
	GameObject(float pX = 0.0f, float pY = 0.0f, std::string pName = "GameObject");
	~GameObject();

	void ClearChildren();

	std::string name;

	GameObject* GetParent() const;
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
	virtual void Update();
	virtual void OnLoad();

	void SetScene(Scene* scene);
	Scene* GetScene() const;

protected:
	bool _canRender = false;
	int _renderLayer = -1;

	//GameObject* _parent = nullptr;
	std::vector <GmObjctPtr> _children;

	int getChildIndex();
	Scene* _scene;

private:
	void setParent(GameObject* pParent);
};

