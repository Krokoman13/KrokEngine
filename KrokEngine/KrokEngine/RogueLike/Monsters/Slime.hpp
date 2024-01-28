#pragma once
#include "Monster.hpp"

class Slime : public GameObject, public Monster
{
public:
	Slime(const Vec2 a_pos);

protected:
	virtual void update() override;
};