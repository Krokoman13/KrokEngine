#include "Detector.hpp"

Detector::Detector(Vec2 pPos) : ImageGameObject("Debug/Redcircle.png", pPos.x, pPos.y)
{
	centered = true;

	tc = new TriggerColliderComponent(new CircleCollider(GetWidth() / 2.f));
	AddComponent(tc);
	tc->onTriggerEnterAction = [this](Collider* pCollider) {this->report("TriggerEnter: ", pCollider); };
	tc->onTriggerExitAction = [this](Collider* pCollider) {this->report("TriggerExit: ", pCollider); };
}

void Detector::report(const std::string& text, Collider* pCollider)
{
	std::cout << text << pCollider->GetColliderComponent()->GetGameObject()->name << std::endl;
}

