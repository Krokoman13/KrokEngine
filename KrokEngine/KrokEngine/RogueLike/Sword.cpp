#include "Sword.hpp"
#include <algorithm>

Sword::Sword() : GameObject(Vec2(0.f, 0.f), "Sword")
{
	const Vec2 offset = Vec2(12, 0);

	m_swordSprite = AddComponent<Sprite>(RS__WEAPON_SWORD_1_PNG);
	m_swordSprite->SetDisplayMode(DisplayMode::Center);
	m_swordSprite->SetLocalPosition(offset);

	m_slashAnimSprite = AddComponent<AnimationSprite>(RS__SLASH_EFFECT_ANIM_SPRITESHEET_PNG, 3, 1, false);
	m_slashAnimSprite->SetDisplayMode(DisplayMode::LeftCenter);
	//m_slashAnimSprite->SetLocalScale(Vec2(2.f, 2.f));
	m_slashAnimSprite->SetLocalPosition(offset);
	AnimationSprite* copy = m_slashAnimSprite;
	m_slashAnimSprite->AddAnimation(Animation(0, 2, 0.1f, [copy]() { copy->SetActive(false); }), "SLASH");
	m_slashAnimSprite->SetActive(false);
}

void Sword::onLoad()
{
	m_pPhysicsScene = dynamic_cast<PhysicsScene*>(GetScene());
	if (!m_pPhysicsScene) std::cout << "Warning: Sword is not in a PhysicsScene";

	GetParent()->TryGetComponent<Sprite>(m_parentSprite);
}

void Sword::update()
{
	if (m_parentSprite) m_swordSprite->SetRenderLayer(m_parentSprite->GetLayer());

	const Vec2 pos = GetGlobalMatrix().GetPos();
	const Vec2 diffrence = Input::MousePos() - pos;

	SetLocalRotation(-diffrence.GetAngleRadians());

	if (diffrence.x > 0.f && !m_isRight)
	{
		m_swordSprite->identity.Scale(Vec2(1, -1));
		m_isRight = true;
	}
	else if (diffrence.x < 0.f && m_isRight) {
		m_swordSprite->identity.Scale(Vec2(1, -1));
		m_isRight = false;
	}

	if (Input::WentDown(Mouse::Button::Left) && !m_slashAnimSprite->IsActive()) startSlash();
}

void Sword::startSlash()
{
	m_slashAnimSprite->SetActive(true);

	slash();
}

void Sword::slash()
{
	GameObject* previous = nullptr;

	for (Collider* colliding : m_pPhysicsScene->OverLayCircle(this, 24))
	{
		GameObject* current = colliding->GetColliderComponent()->GetGameObject();

		if (current == previous) continue;
		previous = current;

		if (previous == GetParent()) continue;

		Health* health = nullptr;
		if (!previous->TryGetComponent<Health>(health)) continue;

		health->GainDamage(2);
	}
}
