#pragma once
#include "../Engine/KrokEngine.hpp"
#include "../Engine/Add-on/Physics.hpp"

class Ball : public GameObject
{
public:
	Ball(Vec2 pos);
	RigidBody* rb;

	void onLoad() override;
	
	void update() override;
};

