#pragma once
#include "../Engine/KrokEngine.hpp"
#include <functional>

class UpdateComponent : public Component
{
private:
	std::function<void()> m_updateFunction;

public:
	UpdateComponent(std::function<void()> a_updateFunction);

protected:
	void Update() override;
};