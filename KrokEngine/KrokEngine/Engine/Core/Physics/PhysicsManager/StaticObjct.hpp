#include "../../../Essentials/GmObjctPtr.hpp"
#include "../ColliderComponent.hpp"

struct StaticObjct
{
	StaticObjct(const GmObjctPtr& pGameObject, ColliderComponent* pTriggerCollider) : gameObject(pGameObject)
	{
		collider = pTriggerCollider;
	}

	GmObjctPtr gameObject;
	ColliderComponent* collider;
};