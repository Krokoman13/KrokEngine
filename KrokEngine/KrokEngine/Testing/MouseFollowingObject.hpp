#pragma once
#pragma once
#include "../Engine/Core/Graphics/ImageGameObject.hpp"
#include "../Engine/Core/Math/Vec2.hpp"

class MouseFollowingObject : public GameObject
{
public:
	MouseFollowingObject();

	virtual void Update() override;

private:
	ImageGameObject* redDot;
	ImageGameObject* blueDot;
};

