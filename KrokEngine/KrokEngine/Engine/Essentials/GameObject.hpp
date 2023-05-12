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
	GameObject(Vec2 position, std::string name = "GameObject", GameObject* parent = nullptr);
	GameObject(float x = 0.0f, float y = 0.0f, std::string name = "GameObject", GameObject* parent = nullptr);
	virtual ~GameObject();

	void ClearChildren();

	std::string name;

	GameObject* GetParent();
	void SetParent(GameObject* parent);

	void ClearParent();

	const std::vector <GmObjctPtr> GetChildren();
	GmObjctPtr GetChild(unsigned int i);

	void AddChild(GmObjctPtr toAdd);
	void RemoveChild(GmObjctPtr toRemove);

	int GetRenderLayer();
	void SetRenderLayer(int renderLayer);
	bool canRender = false;

	virtual sf::Sprite* GetSprite();
	virtual void Update();
	virtual void OnLoad();

	void SetScene(Scene* scene);

protected:
	int _renderLayer = -1;

	//GameObject* _parent = nullptr;
	std::vector <GmObjctPtr> _children;

	//int getPositionAsChild(GameObject* toFind);
	Scene* _scene;
};

