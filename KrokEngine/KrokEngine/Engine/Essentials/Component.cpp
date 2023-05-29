#include "Component.hpp"
#include "GameObject.hpp"
#include <stdexcept>

void Component::SetGameObject(GmObjctPtr pGameObject)
{
	if (pGameObject.Get() == nullptr) throw std::invalid_argument("Component cannot be added to a nullptr");
	if (pGameObject == _gameObject) return;
	if (_gameObject.Get() != nullptr) throw std::logic_error("Components cannot switch gameobjects");

	_gameObject = pGameObject;
}

GmObjctPtr Component::GetGameObject() const
{
	return _gameObject;
}

void Component::OnLoad()
{

}

void Component::Update()
{
}

void Component::OnEnable()
{
}

void Component::OnDisable()
{
}


void Component::SetActive(bool pEnabled)
{
	if (pEnabled == _enabled) return;
	
	_enabled = pEnabled;

	if (_gameObject.Get() == nullptr || _gameObject->IsActive()) return;

	if (_enabled) OnEnable();
	else OnDisable();
}

bool Component::IsActive() const
{
	return _enabled;
}
