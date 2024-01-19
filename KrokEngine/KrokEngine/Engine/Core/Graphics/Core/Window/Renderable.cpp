#include "Renderable.hpp"
#include "../../../../Essentials/GameObject.hpp"

void Renderable::setGameObject(GameObject* a_gameObject)
{
	SetParent(a_gameObject);
}
