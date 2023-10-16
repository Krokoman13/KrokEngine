#include "Ball.hpp"

Ball::Ball(Vec2 pPos) : ImageGameObject("Debug/Bluecircle.png", pPos.x, pPos.y)
{
	centered = true;
	rb = new RigidBody(new CircleCollider(GetWidth() / 2.f));
	rb->bounciness = 0.9f;

	AddComponent(rb);
}

void Ball::update()
{
	Vec2 velocity = Input::mousePosition - GetGlobalPosition();
	rb->velocity = velocity;
}
