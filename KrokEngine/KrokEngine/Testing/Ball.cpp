#include "Ball.hpp"

Ball::Ball(Vec2 pPos) : GameObject("Ball", pPos.x, pPos.y)
{
	Sprite* sprite = AddComponent<Sprite>(RS__BALL_PNG);
	sprite->diffuseColor = Color(0, 0, 255);
	sprite->SetDisplayMode(DisplayMode::Center);

	rb = AddComponent<RigidBody>(new CircleCollider(sprite->GetLocalXScale() / 2.f));
	rb->bounciness = 0.9f;
}

void Ball::update()
{
	Vec2 velocity = Input::mousePosition - GetGlobalPosition();
	rb->velocity = velocity;
}
