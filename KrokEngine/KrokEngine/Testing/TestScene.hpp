#pragma once
#include "../Engine/Add-on/Physics.hpp"
#include "../Engine/KrokEngine.hpp"

class TestScene : public PhysicsScene
{
public:
	TestScene();
	void update() override;
	virtual void onLoad() override;
};

