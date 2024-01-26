#include "Barry.hpp"

Barry::Barry(const Vec2 a_pos) : GameObject(a_pos, "Barry")
{
	m_animSprite = AddComponent<AnimationSprite>(RS__KNIGHT_SPRITESHEET_PNG, 6, 2, false);
	m_animSprite->SetDisplayMode(DisplayMode::Center);
	m_animSprite->SetLocalPosition(Vec2(0, -22.f));
	m_animSprite->SetFilter(GL_NEAREST, GL_NEAREST);
	m_animSprite->AddAnimation(Animation(0, 5, 0.3f), "IDLE");
	m_animSprite->AddAnimation(Animation(6, 11, 0.3f), "RIGHT");
	m_animSprite->SetRenderLayer(1);

	Vec2 offset = Vec2(0, 0);
	float size = 32;
	m_rb = AddComponent<RigidBody>(new CircleCollider(size / 2.f, offset));
	m_rb->bounciness = 0;
	//Sprite* colliderSprite = AddComponent<Sprite>(RS__BALL_PNG);
	//colliderSprite->SetSize(Vec2(size, size));
	//colliderSprite->SetLocalPosition(offset);
}

void Barry::update()
{
	const Vec2 pos = GetGlobalPosition();
	m_animSprite->SetRenderLayer((unsigned int)pos.y / 44.f);

	Vec2 direction;
	float speed = 50.f;

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

	if (direction.x * direction.x > 0.1f)
	{
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
	}

	m_animSprite->GetCurrentAnimation()->speed = speed/25.f;

	direction.SetLength(speed);
	m_rb->velocity = direction;
}
