#include "UpdateComponent.hpp"

UpdateComponent::UpdateComponent(std::function<void()> a_updateFunction) : m_updateFunction(a_updateFunction)
{
}

void UpdateComponent::Update()
{
	m_updateFunction();
}