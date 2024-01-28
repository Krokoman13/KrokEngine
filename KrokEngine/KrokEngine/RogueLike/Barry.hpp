#pragma once
#include "../Engine/Add-on/Physics.hpp"
#include "../Engine/KrokEngine.hpp"

class Barry : public GameObject
{
private:
	AnimationSprite* m_animSprite = nullptr;
	RigidBody* m_rigBody = nullptr;
	enum Direction
	{
		Left, Right
	};
	Direction m_currentDirection = Right;

public:
	Barry(const Vec2 a_pos);

protected:
	virtual void update() override;
};

