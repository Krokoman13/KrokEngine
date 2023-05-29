#pragma once
#include "../../../Essentials/Component.hpp"
#include "../Colliders/LineCollider.hpp"
#include "../Colliders/CircleCollider.hpp"

class ColliderComponent : public Component
{
public:
	ColliderComponent(CircleCollider* toAdd = nullptr);
	virtual ~ColliderComponent();

	const std::vector<CircleCollider*>& GetCircles() const;
	const std::vector<LineCollider*>& GetLines() const;

	void Add(LineCollider* pCollider);
	void Add(CircleCollider* pCollider);
	virtual void SetGameObject(GmObjctPtr pGameObject) override;

	void SetBounciness(float pBouncyness);	//1.0f is 100% bouncy
	float GetBounciness() const;

private:
	float _bounciness = 0.5f;	//1.0f is 100% bouncy
	std::vector<LineCollider*> _lines;
	std::vector<CircleCollider*> _circles;
};

