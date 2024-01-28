#include "SpriteFlipper.hpp"

void SpriteFlipper::OnLoad()
{
	if (!m_myFollowBehaviour && m_gameObject->TryGetComponent<FollowBehaviour>(m_myFollowBehaviour)) return;
	if (!m_myRigidBody) m_gameObject->TryGetComponent<RigidBody>(m_myRigidBody);
}

void SpriteFlipper::OnEnable()
{
	if (!m_mySprite && !m_gameObject->TryGetComponent<Sprite>(m_mySprite))
	{
		std::cout << "WARNING: Spriteflipper is not attached to a gameobject that contains a sprite" << std::endl;
		SetActive(false);
		return;
	}
}

void SpriteFlipper::Update()
{
	if (m_myFollowBehaviour)
	{
		flipBasedOnFollowBehaviour();
		return;

	}
	
	if (m_myRigidBody)
	{
		flipBasedOnRigidBody();
		return;
	}
	
	if (m_gameObject->TryGetComponent<RigidBody>(m_myRigidBody)) return;
	if (m_gameObject->TryGetComponent<FollowBehaviour>(m_myFollowBehaviour)) SetActive(false);
}

void SpriteFlipper::flipBasedOnRigidBody()
{
	flipBasedOnDirection(m_myRigidBody->velocity);
}

void SpriteFlipper::flipBasedOnFollowBehaviour()
{
	const Vec2 target = m_myFollowBehaviour->target->GetGlobalPosition();
	const Vec2 origin = m_gameObject->GetGlobalPosition();

	flipBasedOnDirection(target - origin);
}

void SpriteFlipper::flipBasedOnDirection(const Vec2 a_direction)
{
	if (m_currentDirection != Right && a_direction.x > 0.f)
	{
		m_mySprite->Flip();
		m_currentDirection = Right;
		return;
	}

	if (m_currentDirection != Left && a_direction.x < 0.f)
	{
		m_mySprite->Flip();
		m_currentDirection = Left;
	}
}
