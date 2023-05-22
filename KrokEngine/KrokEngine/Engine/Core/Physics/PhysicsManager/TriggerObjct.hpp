#include "../../../Essentials/GmObjctPtr.hpp"
#include "../TriggerColliderComponent.hpp"

struct TriggerObjct
{
	TriggerObjct(const GmObjctPtr& pGameObject, TriggerColliderComponent* pTriggerCollider) : gameObject(pGameObject)
	{
		triggerCollider = pTriggerCollider;
	}

	GmObjctPtr gameObject;
	TriggerColliderComponent* triggerCollider;
};