#include "ColliderComponent.hpp"

ColliderComponent::ColliderComponent()
{
}

ColliderComponent::ColliderComponent(CircleCollider* a_circleCollider)
{
	Add(a_circleCollider);
}

ColliderComponent::ColliderComponent(LineCollider* a_lineCollider)
{
	Add(a_lineCollider);
}

ColliderComponent::ColliderComponent(const std::vector<Vec2>& a_points)
{
	Add(a_points);
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

void ColliderComponent::Add(const std::vector<Vec2>& a_points)
{
	if (a_points.size() < 1) return;
	Add(new PointCollider(a_points[0]));

	if (a_points.size() < 2) return;

	for (unsigned int i = 1; i < a_points.size(); i++)
	{
		Add(new LineCollider(a_points[i - 1], a_points[i]));
		Add(new PointCollider(a_points[i]));
	}

	Add(new LineCollider(a_points[a_points.size() - 1], a_points[0]));
}

void ColliderComponent::setGameObject(GameObject* pGameObject)
{
	for (Collider* collider : _circles)
	{
		collider->SetParent(pGameObject);
	}

	for (Collider* collider : _lines)
	{
		collider->SetParent(pGameObject);
	}
}
