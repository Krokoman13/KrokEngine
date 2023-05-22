#include "PhysicsManager.hpp"
#include "../../SceneManager/Scene.hpp"
//#include "../../../Essentials/Component.hpp"

void PhysicsManager::Update(Scene* pScene)
{
	Load(pScene->ToLoad());
	updateTriggers();
	updateStatics();
}

void PhysicsManager::Load(const std::vector<GmObjctPtr>& toLoad)
{
	for (GmObjctPtr gameObject : toLoad)
	{
		Component* component = nullptr;
		bool found = false;
		component = gameObject->TryFindComponent(typeid(TriggerColliderComponent), found);

		if (found)
		{
			TriggerColliderComponent* triggerCollider = static_cast<TriggerColliderComponent*>(component);
			TriggerObjct triggerObject(gameObject, triggerCollider);
			_triggerObjects.push_back(triggerObject);
		}

		component = gameObject->TryFindComponent(typeid(ColliderComponent), found);
		if (found)
		{
			ColliderComponent* collider = static_cast<ColliderComponent*>(component);
			StaticObjct triggerObject(gameObject, collider);
			_staticObject.push_back(triggerObject);
		}
	}
}

void PhysicsManager::updateTriggers()
{
	unsigned int i = 0;

	while (i < _triggerObjects.size())
	{
		TriggerObjct triggerObject = _triggerObjects[i];

		if (triggerObject.gameObject.IsDestroyed())
		{
			_triggerObjects.erase(_triggerObjects.begin() + i);
			continue;
		}

		updateTrigger(triggerObject);
		i++;
	}
}

void PhysicsManager::updateStatics()
{
	unsigned int i = 0;

	while (i < _staticObject.size())
	{
		StaticObjct staticObject = _staticObject[i];

		if (staticObject.gameObject.IsDestroyed())
		{
			_staticObject.erase(_staticObject.begin() + i);
			continue;
		}

		updateStatic(staticObject);
		i++;
	}
}

void PhysicsManager::updateTrigger(TriggerObjct& pTriggerObject)
{
	TriggerColliderComponent* triggerCollider = pTriggerObject.triggerCollider;

	bool trigger = false;

	for (StaticObjct other : _staticObject)
	{
		trigger = triggerCollider->Colliding(*other.collider);
		if (trigger) break;
	}

	triggerCollider->SetTriggering(trigger);
}

void PhysicsManager::updateStatic(StaticObjct& pStaticObject)
{
}
