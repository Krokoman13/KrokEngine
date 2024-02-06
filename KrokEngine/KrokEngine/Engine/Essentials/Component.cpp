#include "Component.hpp"
#include "GameObject.hpp"
#include <stdexcept>

Component::Component() : m_gameObject(nullptr)
{
}

Component::~Component()
{
}

void Component::SetGameObject(GameObject* a_gameObject)
{
	if (!a_gameObject) throw std::invalid_argument("Component cannot be added to a nullptr");
	if (a_gameObject == m_gameObject) return;
	if (m_gameObject) throw std::logic_error("Components cannot switch gameobjects");

	m_gameObject = a_gameObject;

	setGameObject(a_gameObject);
}

GameObject* Component::GetGameObject() const
{
	return m_gameObject;
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


void Component::SetActive(const bool a_enabled)
{
	if (a_enabled == m_enabled) return;
	
	m_enabled = a_enabled;

	if (!m_gameObject || !m_gameObject->IsActive()) return;

	if (m_enabled) OnEnable();
	else OnDisable();
}

bool Component::IsActive() const
{
	if (!m_gameObject || !m_gameObject->IsActive()) return false;
	return m_enabled;
}

void Component::setGameObject(GameObject* a_gameObject)
{
}
