#pragma once

#include "../../Engine/Add-on/Physics.hpp"
#include "../../Engine/KrokEngine.hpp"

#include "../Components/FollowBehaviour.hpp"
#include "../Components/Health.hpp"

class Monster
{
protected:
	AnimationSprite* m_animSprite = nullptr;
	RigidBody* m_rigBody = nullptr;
	FollowBehaviour* m_follBehaviour = nullptr;
	Health* health = nullptr;

public:
	void SetTarget(GameObject* m_pTarget) { m_follBehaviour->target = m_pTarget; }
};
