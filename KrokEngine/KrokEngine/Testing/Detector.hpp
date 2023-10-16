#pragma once
#include "../Engine/KrokEngine.hpp"
#include "../Engine/Add-on/Physics.hpp"

class Detector : public ImageGameObject
{
public:
	Detector(Vec2 pos);
	TriggerColliderComponent* tc;

private:
	void report(const std::string& text,RigidBody* pRigidBody);
};

