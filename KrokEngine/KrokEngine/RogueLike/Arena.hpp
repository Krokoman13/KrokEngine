#pragma once
#include "../Engine/Add-on/Physics.hpp"
#include "../Engine/KrokEngine.hpp"

class Arena : public PhysicsScene
{
private:
	const unsigned int m_gridSize = 16;

	GameObject* m_gameOverScreen = nullptr;
	GameObject* m_barry = nullptr;

public:
	Arena() : PhysicsScene("Arena") { _gravity = Vec2(0, 0);  _resistanceCoefficient = 0.f;};

public:
	void onLoad() override;

protected:
	void update() override;

private:
	Vec2 toGrid(const unsigned int a_x, const unsigned int a_y);
};

