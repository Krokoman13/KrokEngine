#pragma once
#include "Monster.hpp"
#include "../Bomb.hpp"

class Goblin : public GameObject, public Monster
{
private:
	const unsigned int m_loadTime = 5;
	unsigned int m_loadDuration = 0;

public:
	Goblin(const Vec2 a_pos);

protected:
	virtual void update() override;
	virtual void attack() override;
};