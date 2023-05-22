#pragma once
#include "../TriggerColliderComponent.hpp"
#include "StaticObjct.hpp"
#include "TriggerObjct.hpp"

class PhysicsManager
{
public:
	void Update(Scene* pScene);
	void Load(const std::vector<GmObjctPtr>& pToLoad);

private:
	void updateTriggers();
	void updateStatics();
	void updateTrigger(TriggerObjct& pTriggerObject);
	void updateStatic(StaticObjct& pStaticObject);

private:
	std::vector<TriggerObjct> _triggerObjects;
	std::vector<StaticObjct> _staticObject;
};

