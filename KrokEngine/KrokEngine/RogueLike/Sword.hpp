#pragma once
#include "../Engine/Add-on/Physics.hpp"
#include "../Engine/KrokEngine.hpp"

#include "Components/Health.hpp"

class Sword : public GameObject
{
private:
	Sprite* m_swordSprite;
	AnimationSprite* m_slashAnimSprite;
	PhysicsScene* m_pPhysicsScene = nullptr;

	bool m_isRight = true;

public:
	Sword();

protected:
	void onLoad() override;
	void update() override;

private:
	void startSlash();
	void slash();
};