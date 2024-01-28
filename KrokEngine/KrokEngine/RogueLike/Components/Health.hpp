#pragma once
#pragma once
#include "../../Engine/Add-on/Physics.hpp"
#include "../../Engine/KrokEngine.hpp"

class Health : public Component
{
private:
	int m_hitPoints = 3;

	float m_invincibleDuration = 0.f;
	float m_invincibleTime = 0.3f;

	bool m_destroyOnDeath = true;

	std::function<void()> m_onInvincibleEnter;
	std::function<void()> m_onInvicibleOver;

	std::function<void()> m_onDeath;

public:
	Health() {};

public:
	void SetHealth(const unsigned int a_hitPoints) { m_hitPoints = a_hitPoints; };
	void SetInvicibleTime(const float a_invicibleTime) {}

	bool IsDead() { return m_hitPoints <= 0; };
	bool IsInvincible() { return m_invincibleDuration > 0.f; };

	void GainDamage(const unsigned int a_hitPoints)
	{
		if (IsDead() || IsInvincible()) return;

		m_hitPoints -= a_hitPoints;

		if (m_hitPoints < 0) m_hitPoints = 0;
		if (m_hitPoints == 0)
		{
			onDeath();
			return;
		}

		if (m_onInvincibleEnter) m_onInvincibleEnter();
		m_invincibleDuration = m_invincibleTime;
	};
	
	void SetOnDeath(const std::function<void()>& a_onDeath) { m_onDeath = a_onDeath; };
	void SetOnInvicibleEnter(const std::function<void()>& a_onInvincibleEnter) { m_onInvincibleEnter = a_onInvincibleEnter; };
	void SetOnInvicibleExit(const std::function<void()>& a_onInvicibleOver) { m_onInvicibleOver = a_onInvicibleOver; };

	void Update() override
	{
		if (!IsInvincible()) return;
		m_invincibleDuration -= Time::DeltaTimeSeconds();
		if (!IsInvincible() && m_onInvicibleOver) m_onInvicibleOver();
	};

private:
	void onDeath() 
	{
		if (m_destroyOnDeath) m_gameObject->LateDestroy();
		if (m_onDeath) m_onDeath();
	};
};

