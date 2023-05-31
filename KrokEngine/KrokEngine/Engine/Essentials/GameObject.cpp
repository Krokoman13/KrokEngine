#include "GameObject.hpp"
#include "../Core/SceneManager/Scene.hpp"
#include "OB_SmartPointers.hpp"

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

	while (!_children.empty())
	{
		deleteChildImm(_children.back() - 1);
	}
}

sf::Sprite* GameObject::GetSprite()
{
	return nullptr;
}

void GameObject::LateDestroy()
{
	GetParent()->migrateChild(this, nullptr);
}

int GameObject::childIndex(GameObject* pChild)
{
	if (!pChild) return -1;

	for (unsigned int i = 0; i < _children.size(); i++)
	{
		if (_children[i].Get() == pChild)
		{
			return i;
		}
	}

	return -1;
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
	return _children[i].borrow();
}

void GameObject::AddChild(owning_ptr<GameObject>&& pChild)
{
	if (pChild.Get() == this)
		throw std::invalid_argument("Cannot add a GameObject to itself");

	if (HasChild(pChild.Get()))
		return;

	GameObject* currentParent = pChild->GetParent();
	if (currentParent)
	{
		currentParent->migrateChild(pChild.Get(), this);
		return;
	}

	if (_scene)
	{
		_scene->AddToScene(pChild.borrow());
	}

	pChild->_parent = this;
	_children.push_back(std::move(pChild));
}

//void GameObject::AddChild(GameObject* pChild)
//{
//	owning_ptr<GameObject> child(pChild);
//	AddChild(pChild);
//}

void GameObject::removeChild(unsigned int pChildIndex)
{
	if (pChildIndex >= _children.size()) throw std::out_of_range("Child index is out of range");

	_children[pChildIndex]->_parent = nullptr;
	_children.erase(_children.begin() + pChildIndex);
}

void GameObject::RemoveChild(GameObject* pChild)
{
	int i = childIndex(pChild);
	if (i < 0) 	throw std::invalid_argument("Could not remove a non-existent child");
	removeChild(i);
}

void GameObject::deleteChildImm(unsigned int pChildIndex)
{
	if (pChildIndex >= _children.size()) throw std::out_of_range("Child index is out of range");

	_children[pChildIndex]->_parent = nullptr;
	_children[pChildIndex].destroy();
	_children.erase(_children.begin() + pChildIndex);
}

void GameObject::deleteChildImm(GameObject* pChild)
{
	int i = childIndex(pChild);
	if (i < 0) 	throw std::invalid_argument("Could not remove a non-existent child");
	deleteChildImm(i);
}

void GameObject::migrateChild(unsigned int pChildIndex, GameObject* pNewParent)
{
	_children[pChildIndex]->_parent = pNewParent;

	if (!pNewParent)
	{
		if (!_scene) _children[pChildIndex].destroy();
		else _scene->Parentless(std::move(_children[pChildIndex]));
		return;
	}

	pNewParent->_children.push_back(std::move(_children[pChildIndex]));
}

void GameObject::migrateChild(GameObject* pChild, GameObject* pNewParent)
{
	int i = childIndex(pChild);
	if (i < 0) 	throw std::invalid_argument("Could not migrate a non-existent child");
	migrateChild(i, pNewParent);

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