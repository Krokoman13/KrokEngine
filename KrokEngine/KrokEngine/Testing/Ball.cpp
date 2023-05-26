#include "Ball.hpp"

Ball::Ball(Vec2 pPos) : ImageGameObject("Debug/Bluecircle.png", pPos.x, pPos.y)
{
	centered = true;
	rb = new RigidBody(new CircleCollider(GetWidth() / 2));
	AddComponent(rb);
}

void Ball::update()
{
	//Vec2 velocity = Input::mousePosition - GetGlobalPosition();
	//rb->velocity = velocity;

	if (Input::WentDown(sf::Mouse::Left))
	{
		//Delete();
	}
}
