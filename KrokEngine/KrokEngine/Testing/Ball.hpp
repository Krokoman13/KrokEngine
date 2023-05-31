#pragma once
#include "../Engine/KrokEngine.hpp"
#include "../Engine/Add-on/Physics.hpp"

class Ball : public ImageGameObject
{
public:
	Ball(Vec2 pos);

	void update() override;

private:
	RigidBody* rb;
};

