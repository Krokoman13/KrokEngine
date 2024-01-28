#pragma once
#include "../../Engine/Add-on/Physics.hpp"
#include "../../Engine/KrokEngine.hpp"

#include "FollowBehaviour.hpp"

class SpriteFlipper : public Component
{
private:
	RigidBody* m_myRigidBody = nullptr;
	FollowBehaviour* m_myFollowBehaviour = nullptr;

	Sprite* m_mySprite = nullptr;

	enum Direction
	{
		Left, Right
	};
	Direction m_currentDirection = Right;

public:
	void OnLoad() override;	
	void OnEnable() override;
	void Update() override;

private:
	void flipBasedOnRigidBody();
	void flipBasedOnFollowBehaviour();

	void flipBasedOnDirection(const Vec2 a_direction);
};