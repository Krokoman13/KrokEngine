#pragma once

#include "../../Engine/Add-on/Physics.hpp"
#include "../../Engine/KrokEngine.hpp"

#include "../Components/FollowBehaviour.hpp"
#include "../Components/Health.hpp"

class Monster
{
private:
	Health* m_targetHealth = nullptr;

protected:
	AnimationSprite* m_animSprite = nullptr;
	RigidBody* m_rigBody = nullptr;
	FollowBehaviour* m_follBehaviour = nullptr;
	Health* m_health = nullptr;

public:
	void SetTarget(GameObject* m_pTarget) { m_follBehaviour->target = m_pTarget; }

	void TryToAttack()
	{
		if (!m_follBehaviour) return;
		if (!m_follBehaviour->found) return;

		attack();
	};

protected:
	virtual void attack() 
	{ 
		if (!m_targetHealth)
		{
			if (!m_follBehaviour->target->TryGetComponent<Health>(m_targetHealth)) return;
		}

		m_targetHealth->GainDamage(1); 
	};
};
