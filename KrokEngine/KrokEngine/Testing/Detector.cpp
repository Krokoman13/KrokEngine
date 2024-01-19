#include "Detector.hpp"

Detector::Detector(Vec2 pPos) : GameObject("Detector", pPos.x, pPos.y)
{
	Sprite* sprite = AddComponent<Sprite>(RS__BALL_PNG);
	sprite->diffuseColor = Color(0, 255, 0);
	sprite->SetDisplayMode(DisplayMode::Center);

	tc = AddComponent <TriggerColliderComponent>(new CircleCollider(sprite->GetLocalXScale() / 2.f));

	tc->onTriggerEnterAction = [this](Collider* pCollider) {this->report("TriggerEnter: ", pCollider); };
	tc->onTriggerExitAction = [this](Collider* pCollider) {this->report("TriggerExit: ", pCollider); };
}

void Detector::report(const std::string& text, Collider* pCollider)
{
	std::cout << text << pCollider->GetColliderComponent()->GetGameObject()->name << std::endl;
}

