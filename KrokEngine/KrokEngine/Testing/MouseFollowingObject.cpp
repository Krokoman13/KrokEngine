#include "MouseFollowingObject.hpp"
#include "../Engine/KrokEngine.hpp"
#include "MouseFollowingBehaviour.hpp"

MouseFollowingObject::MouseFollowingObject() : GameObject("MouseFollowingObject")
{
	AddComponent(new MouseFollowingBehaviour());

	float diameter = 50.0f;
	_redDot = new ImageGameObject("Debug/Redcircle.png");
	_blueDot = new ImageGameObject("Debug/Bluecircle.png");

	_redDot->centered = true;
	_blueDot->centered = true;

	_redDot->SetSize(diameter, diameter);
	_blueDot->SetSize(diameter, diameter);

	AddChild(_redDot);
	AddChild(_blueDot);

	goBlue();

	_triggerCollider = new TriggerColliderComponent(new CircleCollider(diameter / 2.0f));
	//_triggerCollider->onTriggerEnterAction = ([this] {goRed(); });
	//_triggerCollider->onTriggerExitAction = ([this] {goBlue();});
	AddComponent(_triggerCollider);
}

void MouseFollowingObject::update()
{
	bool isTriggering = _triggerCollider->IsColliding();
	_redDot->SetVisible(isTriggering);
	_blueDot->SetVisible(!isTriggering);
}

void MouseFollowingObject::goRed()
{
	_redDot->SetVisible(true);
	_blueDot->SetVisible(false);
}

void MouseFollowingObject::goBlue()
{
	_redDot->SetVisible(false);
	_blueDot->SetVisible(true);
}


