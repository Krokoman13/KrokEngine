#include "Ball.hpp"

Ball::Ball(Vec2 pPos) : GameObject("Ball", pPos.x, pPos.y)
{
	Sprite* sprite = AddComponent<Sprite>(RS__BALL_PNG);
	sprite->diffuseColor = Color::Maroon();
	sprite->SetDisplayMode(DisplayMode::Center);

	rb = AddComponent<RigidBody>(new CircleCollider(128.0f / 2));
	rb->bounciness = 0.9f;
}

void Ball::update()
{
	Vec2 velocity = Input::MousePos() - GetGlobalPosition();
	rb->velocity = velocity;
}
