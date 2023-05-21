#include "GameObject.hpp"
#include "Game.hpp"
#include "GmObjctPtr.hpp"
#include "../Core/Math/Vec2.hpp"

GameObject::GameObject(Vec2 position, std::string name) : Transform(position)
{
	this->name = name;
}

GameObject::GameObject(std::string name, float x, float y) : GameObject(Vec2(x, y), name)
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
	while (ChildCount() > 0)
	{
		GmObjctPtr child = _children.back();
		//_children.pop_back();
		int i = ChildCount() - 1;
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
		pScene->AddToScene(child);
	}

	if (pScene == nullptr)
	{
		if (_scene != nullptr) throw std::logic_error("Setting nullptr Scene should result in destruction! This is not yet implemented!");
		return;
	}

	if (_scene != nullptr)
	{
		throw std::logic_error("Changing the scene of an object is not currently possible.");
		return;
	}

	_scene = pScene;
}

Scene* GameObject::GetScene() const
{
	return _scene;
}

int GameObject::getChildIndex()
{
	GameObject* parent = GetParent();

	for (unsigned int i = 0; i < parent->ChildCount(); i++)
	{
		if (this == parent->GetChild(i))
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

//const std::vector<GmObjctPtr> GameObject::GetChildren() const
//{
//	return _children;
//}

unsigned int GameObject::ChildCount() const
{
	return static_cast<unsigned int>(_children.size());
}

GmObjctPtr GameObject::GetChild(unsigned int i) const
{
	if (i > _children.size()-1) throw std::out_of_range("Child index is out of range");;

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

GmObjctPtr GameObject::AddChild(GameObject* pChild)
{
	GmObjctPtr child = GmObjctPtr(pChild);
	AddChild(child);
	return child;
}

void GameObject::RemoveChild(unsigned int pChild)
{
	if (pChild >= _children.size()) throw std::out_of_range("Child index is out of range");

	_children[pChild]->_parent = nullptr;
	_children.erase(_children.begin() + pChild);
}

void GameObject::RemoveChild(GameObject* pChild)
{
	if (pChild == nullptr) return;

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