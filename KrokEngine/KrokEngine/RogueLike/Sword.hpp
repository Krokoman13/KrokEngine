#pragma once
#include "../Engine/Add-on/Physics.hpp"
#include "../Engine/KrokEngine.hpp"

#include "Components/Health.hpp"

class Sword : public GameObject
{
private:
	Sprite* m_swordSprite;
	AnimationSprite* m_slashAnimSprite;

	bool m_isRight = true;

public:
	Sword();

protected:
	void update() override;
};