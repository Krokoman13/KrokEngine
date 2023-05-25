#pragma once
#include "../Engine/KrokEngine.hpp"

class Ball : public ImageGameObject
{
public:
	Ball(Vec2 pos);

	void update() override;

private:
	RigidBody* rb;
};

