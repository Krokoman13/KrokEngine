#include "MouseFollowingBehaviour.hpp"

void MouseFollowingBehaviour::Update()
{
	Vec2 pos = Input::mousePosition;
	_gameObject->SetGlobalPosition(pos);
}
