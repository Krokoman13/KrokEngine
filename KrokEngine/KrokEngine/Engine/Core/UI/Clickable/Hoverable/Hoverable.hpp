#pragma once
#include "../../../../Essentials/Component.hpp"

class Hoverable : Component
{
private:
	bool m_isOver;

public:
	void Update() override;
};

