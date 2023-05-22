#pragma once
#include "../Engine/KrokEngine.hpp"

class MouseFollowingObject : public GameObject
{
public:
	MouseFollowingObject();
	void update() override;

private:
	void goRed();
	void goBlue();

	ImageGameObject* _redDot;
	ImageGameObject* _blueDot;

	TriggerColliderComponent* _triggerCollider;
};

