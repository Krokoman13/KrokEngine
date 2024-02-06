#include "FollowBehaviour.hpp"

void FollowBehaviour::OnLoad()
{
	if (m_gameObject->TryGetComponent<RigidBody>(m_myRigidBody)) return;
	m_myRigidBody = m_gameObject->AddComponent<RigidBody>();
}

void FollowBehaviour::Update()
{
	m_myRigidBody->velocity = Vec2(0, 0);
	const Vec2 pos = m_gameObject->GetGlobalPosition();

	if (!target) return;

	Vec2 direction = target->GetGlobalPosition() - pos;

	if (found = direction.LengthSquared() < (minDistance * minDistance)) {
		return;
	}

	direction.SetLength(speed);
	m_myRigidBody->velocity = direction;
}
