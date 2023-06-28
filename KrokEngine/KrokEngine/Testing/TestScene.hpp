#pragma once
#include "../Engine/Add-on/Physics.hpp"
#include "../Engine/KrokEngine.hpp"
#include "Ball.hpp"

class TestScene : public PhysicsScene
{
public:
	TestScene();
	void update() override;
	virtual void onLoad() override;

private:
	Ball* _current = nullptr;
};

