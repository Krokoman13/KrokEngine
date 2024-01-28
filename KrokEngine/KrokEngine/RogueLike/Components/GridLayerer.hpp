#pragma once
#include "../../Engine/Add-on/Physics.hpp"
#include "../../Engine/KrokEngine.hpp"

class GridLayerer : public Component
{
private:
	Sprite* m_mySprite = nullptr;

	const float m_ySize = 4;

public:
	void OnEnable() override;
	void Update() override;

private:
	void SetLayer();
};