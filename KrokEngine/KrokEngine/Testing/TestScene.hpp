#pragma once
#include "../Engine/KrokEngine.hpp"

class TestScene : public Scene
{
public:
	TestScene();
	void update() override;
	virtual void onLoad() override;
};

