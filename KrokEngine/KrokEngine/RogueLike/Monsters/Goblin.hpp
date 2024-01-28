#pragma once
#include "Monster.hpp"

class Goblin : public GameObject, public Monster
{
public:
	Goblin(const Vec2 a_pos);

protected:
	virtual void update() override;
};