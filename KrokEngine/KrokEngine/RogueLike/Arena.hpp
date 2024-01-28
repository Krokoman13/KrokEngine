#pragma once
#include "../Engine/Add-on/Physics.hpp"
#include "../Engine/KrokEngine.hpp"

class Arena : public PhysicsScene
{
public:
	Arena() : PhysicsScene("Arena") { _gravity = Vec2(0, 0);  _resistanceCoefficient = 0.f;};

public:
	virtual void onLoad() override;
};

