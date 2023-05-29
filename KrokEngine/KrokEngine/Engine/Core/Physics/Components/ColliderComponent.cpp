#include "ColliderComponent.hpp"

ColliderComponent::ColliderComponent(CircleCollider* pToAdd)
{
	Add(pToAdd);
}

ColliderComponent::~ColliderComponent()
{
	for (LineCollider* line : _lines)
	{
		delete line;
	}

	for (CircleCollider* circle : _circles)
	{
		delete circle;
	}
}

const std::vector<CircleCollider*>& ColliderComponent::GetCircles() const
{
	return _circles;
}

const std::vector<LineCollider*>& ColliderComponent::GetLines() const
{
	return _lines;
}

void ColliderComponent::Add(LineCollider* pCollider)
{
	if (pCollider == nullptr) return;
	pCollider->SetColliderComponent(this);
	_lines.push_back(pCollider);
}

void ColliderComponent::Add(CircleCollider* pCollider)
{
	if (pCollider == nullptr) return;
	pCollider->SetColliderComponent(this);
	_circles.push_back(pCollider);
}

void ColliderComponent::SetGameObject(GmObjctPtr pGameObject)
{
	if (pGameObject.Get() == nullptr) throw std::invalid_argument("Component cannot be added to a nullptr");
	if (pGameObject == _gameObject) return;
	if (_gameObject.Get() != nullptr) throw std::logic_error("Components cannot switch gameobjects");

	_gameObject = pGameObject;

	for (Collider* collider : _circles)
	{
		collider->SetParent(pGameObject);
	}

	for (Collider* collider : _lines)
	{
		collider->SetParent(pGameObject);
	}
}

void ColliderComponent::SetBounciness(float pBouncyness)
{
	_bounciness = pBouncyness;
}

float ColliderComponent::GetBounciness() const
{
	return _bounciness;
}
