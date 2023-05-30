#include "TriggerColliderComponent.hpp"

TriggerColliderComponent::TriggerColliderComponent(CircleCollider* pToAdd) : ColliderComponent(pToAdd)
{
}

TriggerColliderComponent::~TriggerColliderComponent()
{
}

void TriggerColliderComponent::OnTriggerEnter()
{
	onTriggerEnterAction();
}

void TriggerColliderComponent::OnTriggerExit()
{
	onTriggerExitAction();
}

bool TriggerColliderComponent::GetTriggering() const
{
	return _triggering;
}

void TriggerColliderComponent::SetTriggering(const bool pTrigger)
{
	if (_triggering == pTrigger) return;

	_triggering = pTrigger;
	if (_triggering) OnTriggerEnter();
	else OnTriggerExit();
}
