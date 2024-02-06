#include "Barry.hpp"

#include "Components/SpriteFlipper.hpp"
#include "Components/GridLayerer.hpp"
#include "Components/Health.hpp"

#include "Sword.hpp"

Barry::Barry(const Vec2 a_pos) : GameObject(a_pos, "Barry")
{
	float size = 16.f;

	m_animSprite = AddComponent<AnimationSprite>(RS__KNIGHT_SPRITESHEET_PNG, 6, 2, false);
	m_animSprite->SetDisplayMode(DisplayMode::BottomCenter);
	m_animSprite->AddAnimation(Animation(0, 5, 0.1f), "IDLE");
	m_animSprite->AddAnimation(Animation(6, 11, 0.1f), "RIGHT");
	m_animSprite->SetRenderLayer(1);

	m_rigBody = AddComponent<RigidBody>();
	float colliderSize = 10;
	Vec2 colliderOffset = Vec2(0, -colliderSize / 2.f);
	m_rigBody->Add(new CircleCollider(colliderSize / 2.f, colliderOffset));
	m_rigBody->bounciness = 0;

	Health* health = AddComponent<Health>();
	health->destroyOnDeath = false;
	health->SetHealth(3);
	Sprite* sprite = m_animSprite;
	health->SetOnInvicibleEnter([sprite]() { sprite->diffuseColor = Color::Red(); });
	health->SetOnInvicibleExit([sprite]() { sprite->diffuseColor = Color::White(); });
	health->SetOnDeath([this]() { 
			PhysicsScene* scene = static_cast<PhysicsScene*>(this->GetScene()->GetScene()); 
			scene->SetPhyicsSpeed(0.f);
		});

	AddComponent<SpriteFlipper>();
	AddComponent<GridLayerer>();

	Sword* sword = new Sword();
	sword->SetLocalPosition(Vec2(0, -6));
	AddChild(sword);
}

void Barry::update()
{
	Vec2 direction;
	float speed = 25.f;

	if (Input::IsPressed(Keyboard::Key::W)) direction.y = -1.f;
	else if (Input::IsPressed(Keyboard::Key::S)) direction.y = 1.f;

	if (Input::IsPressed(Keyboard::Key::D)) direction.x = 1.f;
	else if (Input::IsPressed(Keyboard::Key::A)) direction.x = -1.f;

	if (direction.LengthSquared() < 0.1f)
	{
		m_animSprite->SetCurrentAnimation("IDLE");
		m_rigBody->velocity = direction;
		return;
	}

	m_animSprite->SetCurrentAnimation("RIGHT");

	//m_animSprite->GetCurrentAnimation()->speed = speed/25.f;

	direction.SetLength(speed);
	m_rigBody->velocity = direction;
}
