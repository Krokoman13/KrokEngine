#include "MovingObject.hpp"
#include <cmath>
#include <string>

MovingObject::MovingObject(float x, float y) : ImageGameObject("Smiley.jpg", x, y)
{
	i = 0;
	SetSize(1000, 1000);
	centered = true;
}

void MovingObject::update()
{
	i += 0.001f;
	Vec2 scale = GetLocalScale();
	float value = ((float)std::sin(i)) / 10.0f + 0.5f;
	scale = Vec2(value, value);
	SetLocalRotation(i);
	scale *= 0.999f;
	SetLocalScale(scale);
}
