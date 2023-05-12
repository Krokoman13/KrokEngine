#include "MovingObject.hpp"
#include <cmath>
#include <string>

MovingObject::MovingObject(float x, float y) : ImageGameObject("Smiley.jpg", x, y)
{
	i = 0;
	SetSize(1000, 1000);
	centered = true;
	//CenterImageAround(GetLocalPosition());
}

void MovingObject::Update()
{
	i += 0.001;
	Vec2 scale = this->GetLocalScale();
	float value = ((float)std::sin(i)) / 10.0f + 0.5f;
	scale = value;
	this->SetLocalRotation(i);
	scale *= 0.999f;
	this->SetLocalScale(scale);
}
