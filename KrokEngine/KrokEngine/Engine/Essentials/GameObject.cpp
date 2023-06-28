#include "GameObject.hpp"
#include "../Core/SceneManager/Scene.hpp"

GameObject::GameObject(Vec2 position, std::string name) : Transform(position)
{
	this->name = name;
}

GameObject::GameObject(std::string name, float x, float y) : GameObject(Vec2(x, y), name)
{
}

GameObject::~GameObject()
{
	if (!_scene) return;

	for (unsigned int i = 0; i < _children.size(); i++)
	{
		_scene->Parentless(_children[i]);
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
		if (_children[i].get() == pChild)
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

	_scene = pScene;
	_scene->AddToScene(this);

	for (unsigned int i = 0; i < _children.size(); i++)
	{
		_children[i]->SetScene(pScene);
	}
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
		Component* component = _components[i].get();

		if (!component->IsActive()) continue;
		component->OnEnable();
	}

	//onEnable();
}

void GameObject::OnDisable()
{
	for (unsigned int i = 0; i < _components.size(); i++)
	{
		Component* component = _components[i].get();

		if (!component->IsActive()) continue;
		component->OnDisable();
	}
	//onDisable();
}

const std::vector<std::unique_ptr<Component>>& GameObject::GetComponents() const
{
	return _components;
}

void GameObject::AddComponent(Component* pComponent)
{	
	pComponent->SetGameObject(this);
	std::unique_ptr<Component> componentPtr(pComponent);
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
		if (pOther == _children[i].get())
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

GameObject* GameObject::GetChild(unsigned int i) const
{
	if (i > _children.size()-1) throw std::out_of_range("Child index is out of range");;
	return _children[i].get();
}

void GameObject::AddChild(GameObject* pChild)
{
	if (pChild == this) throw std::invalid_argument("Cannot add a GameObject to itself");

	if (pChild->GetParent() == this) return;

	GameObject* currentParent = pChild->GetParent();
	if (currentParent)
	{
		currentParent->migrateChild(pChild, this);
		return;
	}

	if (_scene)
	{
		pChild->SetScene(_scene);
	}

	pChild->_parent = this;
	_children.push_back(std::unique_ptr<GameObject>(pChild));
}

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

void GameObject::migrateChild(unsigned int pChildIndex, GameObject* pNewParent)
{
	std::unique_ptr<GameObject>& child = _children[pChildIndex];

	Matrix3 globalMatrix = child->GetGlobalMatrix();
	child->_parent = pNewParent;
	child->SetGlobalMatrix(globalMatrix);

	if (!pNewParent)
	{
		if (_scene)
		{
			_scene->Parentless(child);
			_children.erase(_children.begin() + pChildIndex);
		}
		else removeChild(pChildIndex);
		return;
	}

	pNewParent->_children.push_back(std::move(child));
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