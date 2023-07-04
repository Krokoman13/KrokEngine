#include "ColliderComponent.hpp"

ColliderComponent::ColliderComponent(CircleCollider* pToAdd)
{
	Add(pToAdd);
}

ColliderComponent::ColliderComponent(const std::vector<Vec2>& pPoints)
{
	if (pPoints.size() < 1) return;
	Add(new PointCollider(pPoints[0]));

	if (pPoints.size() < 2) return;

	for (unsigned int i = 1; i < pPoints.size(); i++)
	{
		Add(new LineCollider(pPoints[i - 1], pPoints[i]));
		Add(new PointCollider(pPoints[i]));
	}

	Add(new LineCollider(pPoints[pPoints.size() - 1], pPoints[0]));
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

void ColliderComponent::SetGameObject(GameObject* pGameObject)
{
	if (pGameObject == nullptr) throw std::invalid_argument("Component cannot be added to a nullptr");
	if (pGameObject == _gameObject) return;
	if (_gameObject != nullptr) throw std::logic_error("Components cannot switch gameobjects");

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
