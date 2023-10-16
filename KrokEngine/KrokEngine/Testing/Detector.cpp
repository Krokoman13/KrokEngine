#include "Detector.hpp"

Detector::Detector(Vec2 pPos) : ImageGameObject("Debug/Redcircle.png", pPos.x, pPos.y)
{
	centered = true;

	tc = new TriggerColliderComponent(new CircleCollider(GetWidth() / 2.f));
	AddComponent(tc);
	tc->onTriggerEnterAction = [this](RigidBody* pRigidbody) {this->report("TriggerEnter: ", pRigidbody); };
	tc->onTriggerExitAction = [this](RigidBody* pRigidbody) {this->report("TriggerExit: ", pRigidbody); };
}

void Detector::report(const std::string& text, RigidBody* pRigidBody)
{
	std::cout << text << pRigidBody->GetGameObject()->name << std::endl;
}

