#pragma once
#include "../../Engine/KrokEngine.hpp"
#include "Health.hpp"

class Burnable : public Component
{
private:
	float m_toBurnTimeSeconds = 0;
	float m_burnTimerSeconds = 0;
	unsigned int m_damagePerSecond = 0;
	Health* m_health = nullptr;
	Sprite* m_sprite = nullptr;

	TextureShader m_defaultShader;
	Shader m_burnShader;

public:
	Burnable() {};

public:
	void OnLoad() override;
	void Update() override;

	bool IsBurning() { return m_burnTimerSeconds < m_toBurnTimeSeconds; };

	void StartBurning(const float a_durationInSeconds, const unsigned int a_damagePerSecond);
	void StopBurning();
};

