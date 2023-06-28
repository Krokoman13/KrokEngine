#pragma once
#include "../Engine/Add-on/Physics.hpp"
#include "../Engine/KrokEngine.hpp"

class PolyshapeCollisionTester : public PhysicsScene
{
public:
	PolyshapeCollisionTester();
	void update() override;
	void launchShape();
	void buildShape();
	virtual void onLoad() override;

private:
	std::vector<Vec2> _points;
	std::vector<ImageGameObject*> _display;

	RigidBody* _current = nullptr;
	float rotateSpeed = 0.1f;

	void addPoint(const Vec2 pPos);
	void addLine(const Vec2& pStart, const Vec2& pEnd);
};

