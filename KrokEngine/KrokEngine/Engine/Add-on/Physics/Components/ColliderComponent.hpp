#pragma once
#include "../../../Essentials/Component.hpp"
#include "../Colliders/LineCollider.hpp"
#include "../Colliders/CircleCollider.hpp"
#include "../Colliders/PointCollider.hpp"

class ColliderComponent : public Component
{
protected:
	ColliderComponent();

public:
	ColliderComponent(CircleCollider* a_circleCollider);
	ColliderComponent(LineCollider* a_lineCollider);
	ColliderComponent(const std::vector<Vec2>& a_points);
	virtual ~ColliderComponent();

	const std::vector<CircleCollider*>& GetCircles() const;
	const std::vector<LineCollider*>& GetLines() const;

	void Add(LineCollider* pCollider);
	void Add(CircleCollider* pCollider);
	void Add(const std::vector<Vec2>& a_points);

	float bounciness = 0.5f;	//1.0f is 100% bouncy

protected:
	virtual void setGameObject(GameObject* pGameObject) override;

private:
	std::vector<LineCollider*> _lines;
	std::vector<CircleCollider*> _circles;
};

