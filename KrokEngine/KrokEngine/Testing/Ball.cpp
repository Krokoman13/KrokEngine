#include "Ball.hpp"

Ball::Ball(Vec2 pPos) : ImageGameObject("Debug/Bluecircle.png", pPos.x, pPos.y)
{
	centered = true;
	//rb = nullptr;
	rb = new RigidBody(new CircleCollider(GetWidth() / 2));

	rb->bounciness = 0.9f;
	AddComponent(rb);
}

//void Ball::update()
//{
//	//Vec2 velocity = Input::mousePosition - GetGlobalPosition();
//	//rb->velocity = velocity;
//
//	if (Input::WentDown(sf::Mouse::Left))
//	{
//		//LateDestroy();
//	}
//}
