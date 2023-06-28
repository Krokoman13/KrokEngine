#pragma once
#include "../Engine/KrokEngine.hpp"

class PhysicsLine : public GameObject
{
public:
	PhysicsLine(Vec2 pStart, Vec2 pEnd);

private:
	ImageGameObject* _inbetween;
};

