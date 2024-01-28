#include "Barry.hpp"

Barry::Barry(const Vec2 a_pos) : GameObject(a_pos, "Barry")
{
	float size = 16.f;

	m_animSprite = AddComponent<AnimationSprite>(RS__KNIGHT_SPRITESHEET_PNG, 6, 2, false);
	m_animSprite->SetDisplayMode(DisplayMode::BottomCenter);
	m_animSprite->AddAnimation(Animation(0, 5, 0.1f), "IDLE");
	m_animSprite->AddAnimation(Animation(6, 11, 0.1f), "RIGHT");
	m_animSprite->SetRenderLayer(1);
	//m_animSprite->SetActive(false);

	float colliderSize = 10;
	Vec2 colliderOffset = Vec2(0, -colliderSize / 2.f);

	m_rb = AddComponent<RigidBody>(new CircleCollider(colliderSize / 2.f, colliderOffset));
	m_rb->bounciness = 0;

	//Sprite* colliderSprite = AddComponent<Sprite>(RS__BALL_PNG);
	//colliderSprite->SetDisplayMode(DisplayMode::Center);
	//colliderSprite->SetSize(Vec2(colliderSize, colliderSize));
	//colliderSprite->SetLocalPosition(colliderOffset);
}

void Barry::update()
{
	const Vec2 pos = GetGlobalPosition();
	m_animSprite->SetRenderLayer((unsigned int)pos.y / 16.f);

	Vec2 direction;
	float speed = 25.f;

	if (Input::IsPressed(Keyboard::Key::W)) direction.y = -1.f;
	else if (Input::IsPressed(Keyboard::Key::S)) direction.y = 1.f;

	if (Input::IsPressed(Keyboard::Key::D)) direction.x = 1.f;
	else if (Input::IsPressed(Keyboard::Key::A)) direction.x = -1.f;

	if (direction.LengthSquared() < 0.1f)
	{
		m_animSprite->SetCurrentAnimation("IDLE");
		m_rb->velocity = direction;
		return;
	}

	m_animSprite->SetCurrentAnimation("RIGHT");

	if (direction.x > 0.f && m_currentDirection != Right)
	{
		m_animSprite->Flip();
		m_currentDirection = Right;
	}
	else if (direction.x < 0.f && m_currentDirection != Left)
	{
		m_animSprite->Flip();
		m_currentDirection = Left;
	}

	//m_animSprite->GetCurrentAnimation()->speed = speed/25.f;

	direction.SetLength(speed);
	m_rb->velocity = direction;
}
