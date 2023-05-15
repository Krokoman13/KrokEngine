#include "GameObject.hpp"
#include "Game.hpp"
#include "GmObjctPtr.hpp"
#include "../Core/Math/Vec2.hpp"

GameObject::GameObject(Vec2 position, std::string name) : Transform(position)
{
	//this->SetLocalPosition(position);
	this->name = name;
}

GameObject::GameObject(float x, float y, std::string name) : GameObject(Vec2(x, y), name)
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
		//_children.pop_back();
		int i = _children.size() - 1;
		RemoveChild(i);
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

void GameObject::SetScene(Scene* pScene)
{
	if (pScene == _scene) return;

	for (GmObjctPtr child : _children)
	{
		child->SetScene(pScene);
	}

	if (pScene == nullptr)
	{
		if (_scene != nullptr) throw std::logic_error("Setting nullptr Scene should result in destruction! This is not yet implemented!");
		return;
	}

	_scene = pScene;
	OnLoad();
}

Scene* GameObject::GetScene() const
{
	return _scene;
}

int GameObject::getChildIndex()
{
	const std::vector<GmObjctPtr> siblings = GetParent()->GetChildren();

	for (unsigned int i = 0; i < siblings.size(); i++)
	{
		if (this == siblings[i].Get())
		{
			return i;
		}
	}

	return -1;
}

void GameObject::setParent(GameObject* pParent)
{
	if (pParent == GetParent()) return;

	ClearParent();

	if (pParent == nullptr) return;

	_parent = pParent;
	SetScene(pParent->_scene);
}

GameObject* GameObject::GetParent() const
{
	return (GameObject*)_parent;
}

void GameObject::SetParent(GameObject* pParent)
{
	setParent(pParent);
	if (pParent == nullptr) return;
	pParent->AddChild(this);
}

void GameObject::ClearParent()
{
	if (_parent != nullptr)
	{
		GetParent()->RemoveChild(this);
		//_parent = nullptr;
	}
}

bool GameObject::HasChild(GmObjctPtr pOther) const
{
	if (pOther.Get() == nullptr) return false;

	for (unsigned int i = 0; i < this->_children.size(); i++)
	{
		if (pOther == this->_children[i])
		{
			return true;
		}
	}

	return false;
}

const std::vector<GmObjctPtr> GameObject::GetChildren() const
{
	return _children;
}

GmObjctPtr GameObject::GetChild(unsigned int i) const
{
	if (i > _children.size()-1) return nullptr;

	return _children[i];
}

void GameObject::AddChild(GmObjctPtr pChild)
{
	if (pChild.Get() == nullptr) throw std::invalid_argument("Cannot add a non-existing GameObject");

	pChild->ClearParent();

	if (pChild.Get() == this) throw std::invalid_argument("Cannot add a GameObject to itself");

	if (HasChild(pChild)) return;
	_children.push_back(pChild);
	pChild->setParent(this);;
}

void GameObject::RemoveChild(int pChild)
{
	_children[pChild]->_parent = nullptr;
	_children.erase(_children.begin() + pChild);
}

void GameObject::RemoveChild(GmObjctPtr pChild)
{
	if (pChild.Get() == nullptr) return;

	for (unsigned int i = 0; i < this->_children.size(); i++)
	{
		if (this->_children[i] == pChild)
		{
			RemoveChild(i);
			return;
		}
	}

	throw std::invalid_argument("Could not remove a non-existent child");
}

int GameObject::GetRenderLayer() const
{
	GameObject* parent = this->GetParent();

	if (this->_renderLayer >= 0 || parent == nullptr) return this->_renderLayer;

	return parent->GetRenderLayer();
}

bool GameObject::CanRender() const
{
	return _canRender;
}

void GameObject::SetRenderLayer(int renderLayer)
{
	if (renderLayer < -1) renderLayer = -1;
	this->_renderLayer = renderLayer;
}