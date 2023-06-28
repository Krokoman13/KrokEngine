#pragma once
#include "../Engine/Add-on/Physics.hpp"
#include "../Engine/KrokEngine.hpp"

class GravityTest : public PhysicsScene
{
public:
	GravityTest();
	virtual void onLoad() override;
	virtual void update() override;

private:
	RigidBody* _current;

	void build(unsigned int pI);
	static void addLinesTo(GameObject* pGameObject, const std::vector<Vec2>& pPoints);
	static GameObject* createLine(const Vec2& pStart, const Vec2& pEnd);
};
