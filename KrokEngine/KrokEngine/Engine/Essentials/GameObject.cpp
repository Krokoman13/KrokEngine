#include "GameObject.hpp"
#include "../Core/SceneManager/Scene.hpp"
#include "OB_SmartPointers.hpp"

GameObject::GameObject(Vec2 position, std::string name) : Transform(position), _ptr(this)
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
		borrow_ptr<GameObject> child = _children.back();
		RemoveChild(ChildCount() - 1);
		child->Delete();
	}
}

sf::Sprite* GameObject::GetSprite()
{
	return nullptr;
}

void GameObject::Delete()
{
	_ptr.destroy();
}

void GameObject::update()
{
}

void GameObject::onLoad()
{
}

void GameObject::SetScene(Scene* pScene)
{
	if (pScene == _scene) return;

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

	for (unsigned int i = 0; i < _children.size(); i++)
	{
		_children[i]->SetScene(pScene);
	}

	_scene = pScene;

	if (pScene == this) return;

	_scene->AddToScene(_ptr.borrow());
}

Scene* GameObject::GetScene() const
{
	return _scene;
}

void GameObject::SetActive(bool pEnabled)
{
	if (pEnabled == _enabled) return;

	_enabled = pEnabled;

	for (unsigned int i = 0; i < _children.size(); i++)
	{
		_children[i]->SetActive(_enabled);
	}

	if (_enabled) OnEnable();
	else OnDisable();
}

bool GameObject::IsActive() const
{
	return _enabled;
}

void GameObject::Update()
{
	for (unsigned int i = 0; i < _components.size(); i++)
	{
		_components[i]->Update();
	}

	update();
}

void GameObject::OnLoad()
{
	SetActive(true);

	for (unsigned int i = 0; i < _components.size(); i++)
	{
		_components[i]->OnLoad();
	}

	onLoad();
}

void GameObject::OnEnable()
{
	for (unsigned int i = 0; i < _components.size(); i++)
	{
		Component* component = _components[i].Get();

		if (!component->IsActive()) continue;
		component->OnEnable();
	}

	//onEnable();
}

void GameObject::OnDisable()
{
	for (unsigned int i = 0; i < _components.size(); i++)
	{
		Component* component = _components[i].Get();

		if (!component->IsActive()) continue;
		component->OnDisable();
	}
	//onDisable();
}

borrow_ptr<GameObject> GameObject::GetBorrowPtr() const
{
	return _ptr.borrow();
}

void GameObject::setParent(GameObject* pParent)
{
	if (pParent == GetParent()) return;

	ClearParent();
	_parent = pParent;

	if (_parent == nullptr)
	{
		_scene->Parentless(_ptr.borrow());
		return;
	}

	SetScene(pParent->_scene);
}

void GameObject::AddComponent(Component* pComponent)
{	
	pComponent->SetGameObject(this);
	owning_ptr<Component> componentPtr(pComponent);
	_components.push_back(std::move(componentPtr));
}

GameObject* GameObject::GetParent() const
{
	return (GameObject*)_parent;
}

void GameObject::ClearParent()
{
	if (_parent != nullptr)
	{
		GetParent()->RemoveChild(this);
		_parent = nullptr;
	}
}

bool GameObject::HasChild(GameObject* pOther) const
{
	if (pOther == nullptr) return false;

	for (unsigned int i = 0; i < this->_children.size(); i++)
	{
		if (pOther == _children[i].Get())
		{
			return true;
		}
	}

	return false;
}

unsigned int GameObject::ChildCount() const
{
	return static_cast<unsigned int>(_children.size());
}

borrow_ptr<GameObject> GameObject::GetChild(unsigned int i) const
{
	if (i > _children.size()-1) throw std::out_of_range("Child index is out of range");;
	return _children[i];
}

void GameObject::AddChild(borrow_ptr<GameObject> pChild)
{
	if (pChild.Get() == this) throw std::invalid_argument("Cannot add a GameObject to itself");

	pChild->ClearParent();

	if (HasChild(pChild.Get())) return;
	_children.push_back(pChild);
	pChild->setParent(this);;
}

void GameObject::AddChild(GameObject* pChild)
{
	borrow_ptr<GameObject> child = pChild->GetBorrowPtr();
	AddChild(child);
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

	for (unsigned int i = 0; i < _children.size(); i++)
	{
		if (_children[i].Get() == pChild)
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