#include "Burnable.hpp"
#include "../../Engine/Core/Graphics/ResourceManager/ResourceManager.hpp"

void Burnable::OnLoad()
{
	if (!m_health) m_gameObject->TryGetComponent<Health>(m_health);
	if (!m_sprite) m_gameObject->TryGetComponent<Sprite>(m_sprite);

	m_burnShader = ResourceManager::GetShader(RS__FIREEFFECT_VERT, RS__FIREEFFECT_FRAG);		  
}

void Burnable::Update()
{
	if (!IsBurning()) return;
	
	m_burnTimerSeconds += Time::DeltaTimeSeconds();

	while (m_burnTimerSeconds >= 1.0f) {
		m_health->GainDamage(m_damagePerSecond);
		m_burnTimerSeconds -= 1.0f;
		m_toBurnTimeSeconds -= 1.0f;
	}

	if (!IsBurning()) {
		StopBurning();
		return;
	}

	glUseProgram(m_burnShader.GetProgramID());
	glUniform1f(m_burnShader.GetUniform("time"), m_burnTimerSeconds);
	const Color fireColor = Color(242, 125, 12);
	glUniform4f(m_burnShader.GetUniform("fireColor"), fireColor.GetRedUnit(), fireColor.GetGreenUnit(), fireColor.GetBlueUnit(), fireColor.GetAlphaUnit());
}

void Burnable::StartBurning(const float a_burnDurationInSeconds, const unsigned int a_damagePerSecond)
{
	m_burnTimerSeconds = 0;
	m_toBurnTimeSeconds = a_burnDurationInSeconds;
	m_damagePerSecond = a_damagePerSecond;

	m_defaultShader = m_sprite->GetShader();
	m_sprite->SetShader(m_burnShader);
}

void Burnable::StopBurning()
{
	m_burnTimerSeconds = 0;
	m_sprite->SetShader(m_defaultShader);
}
