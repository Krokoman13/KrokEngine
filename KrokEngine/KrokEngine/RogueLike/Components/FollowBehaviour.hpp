#pragma once
#include "../../Engine/Add-on/Physics.hpp"
#include "../../Engine/KrokEngine.hpp"

class FollowBehaviour : public Component
{
private:
	RigidBody* m_myRigidBody = nullptr;

public:
	GameObject* target = nullptr;

	float speed = 10.f;
	float minDistance = 16.f;
	bool found = false;

public:
	void OnLoad() override;
	void Update() override;
};

