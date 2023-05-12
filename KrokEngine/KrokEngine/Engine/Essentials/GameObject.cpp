#include "GameObject.hpp"
#include "Game.hpp"
#include "GmObjctPtr.hpp"
#include "../Core/Math/Vec2.hpp"

GameObject::GameObject(Vec2 position, std::string name, GameObject* parent) : Transform(position)
{
	//this->SetLocalPosition(position);
	this->name = name;

	if (parent != nullptr)
	{
		parent->AddChild(this);
	}
}

GameObject::GameObject(float x, float y, std::string name, GameObject* parent) : GameObject(Vec2(x, y), name, parent)
{
}

GameObject::~GameObject()
{
	if (_parent != nullptr)
	{
		GetParent()->RemoveChild(this);
	}

	ClearChildren();
}

void GameObject::ClearChildren()
{
	while (_children.size() > 0)
	{
		GmObjctPtr child = _children.back();
		_children.pop_back();
		child.DeleteGameObject();
	}
}

sf::Sprite* GameObject::GetSprite()
{
	return nullptr;
}

void GameObject::Update()
{
}

void GameObject::OnLoad()
{
}

void GameObject::SetScene(Scene* scene)
{
	this->_scene = scene;
}

GameObject* GameObject::GetParent()
{
	return (GameObject*)_parent;
}

void GameObject::SetParent(GameObject* newParent)
{
	if (newParent == GetParent()) return;

	if (newParent == nullptr)
	{
		ClearParent();
		return;
	}

	_parent = newParent;
	newParent->AddChild(this);
}

void GameObject::ClearParent()
{
	if (_parent != nullptr)
	{
		GetParent()->RemoveChild(this);
	}
}

const std::vector<GmObjctPtr> GameObject::GetChildren()
{
	return _children;
}

GmObjctPtr GameObject::GetChild(unsigned int i)
{
	if (i > _children.size()-1) return nullptr;

	return _children[i];
}

void GameObject::AddChild(GmObjctPtr toAdd)
{
	if (toAdd.Get() == nullptr) throw std::invalid_argument("Cannot add a non-existing GameObject");

	toAdd->ClearParent();

	if (toAdd.Get() == this) throw std::invalid_argument("Cannot add a GameObject to itself");

	if (std::count(_children.begin(), _children.end(), toAdd)) return;
	_children.push_back(toAdd);
	toAdd->_parent = this;
}

void GameObject::RemoveChild(GmObjctPtr toRemove)
{
	if (toRemove.Get() == nullptr) return;

	for (unsigned int i = 0; i < this->_children.size(); i++)
	{
		if (this->_children[i] == toRemove)
		{
			this->_children.erase(this->_children.begin()+i);
			toRemove->_parent = nullptr;
			return;
		}
	}

	//throw std::invalid_argument("Could not remove a non-existent child");
}

int GameObject::GetRenderLayer()
{
	GameObject* parent = this->GetParent();

	if (this->_renderLayer >= 0 || parent == nullptr) return this->_renderLayer;

	return parent->GetRenderLayer();
}

void GameObject::SetRenderLayer(int renderLayer)
{
	if (renderLayer < -1) renderLayer = -1;
	this->_renderLayer = renderLayer;
}