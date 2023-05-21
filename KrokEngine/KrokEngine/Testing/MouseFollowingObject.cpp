#include "MouseFollowingObject.hpp"
#include "../Engine/KrokEngine.hpp"

MouseFollowingObject::MouseFollowingObject() : GameObject("MouseFollowingObject")
{
	redDot = new ImageGameObject("Debug/Redcircle.png");
	blueDot = new ImageGameObject("Debug/Bluecircle.png");

	redDot->centered = true;
	blueDot->centered = true;

	AddChild(redDot);
	AddChild(blueDot);

	redDot->SetVisible(false);
}

void MouseFollowingObject::Update()
{
	Vec2 pos = Input::mousePosition;
	SetGlobalPosition(pos);

	bool pressed = Input::IsPressed(sf::Mouse::Left);
	redDot->SetVisible(pressed);
	blueDot->SetVisible(!pressed);
}
