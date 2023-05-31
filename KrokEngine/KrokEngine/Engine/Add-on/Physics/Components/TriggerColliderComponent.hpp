#pragma once
#include "ColliderComponent.hpp"
#include <functional>

/// <summary>
/// Component to check for collisions, does not keep track of those collisions currently! 
/// Only if there are any!
/// </summary>

class TriggerColliderComponent : public ColliderComponent
{
public:
	TriggerColliderComponent(CircleCollider* pToAdd = nullptr);
	virtual ~TriggerColliderComponent();

	void OnTriggerEnter();
	void OnTriggerExit();

	bool GetTriggering() const;
	void SetTriggering(const bool pTrigger);

public:
	std::function<void()> onTriggerEnterAction;
	std::function<void()> onTriggerExitAction;

private:
	bool _triggering = false;
};
