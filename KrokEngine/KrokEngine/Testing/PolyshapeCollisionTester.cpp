#include "PolyshapeCollisionTester.hpp"
#include "MovingObject.hpp"

PolyshapeCollisionTester::PolyshapeCollisionTester() : PhysicsScene("PolyshapeCollisionTester")
{
	_resistanceCoefficient = 0;
}

void PolyshapeCollisionTester::update()
{
	if (_current != nullptr)
	{
		_current->GetGameObject()->SetGlobalPosition(Input::mousePosition);

		float rotation = _current->GetGameObject()->GetLocalRotationRad();

		if (Input::IsPressed(sf::Keyboard::A)) _current->GetGameObject()->SetLocalRotation(rotation - rotateSpeed);
		else if (Input::IsPressed(sf::Keyboard::D)) _current->GetGameObject()->SetLocalRotation(rotation + rotateSpeed);
	}

	if (Input::WentUp(sf::Mouse::Left))
	{
		launchShape();
	}

	if (Input::WentDown(sf::Mouse::Left))
	{
		buildShape();
	}
	
	if (Input::WentDown(sf::Mouse::Right))
	{
		addPoint(Input::mousePosition);
	}
}

void PolyshapeCollisionTester::launchShape()
{
	if (_current == nullptr) return;

	Vec2 direction = Input::mousePosition - Input::previousMousePosition;
	direction *= (1 / sceneManager->GetGame()->deltaSeconds);
	direction /= 100.0f;

	_current->velocity = direction;
	_current = nullptr;
}

void PolyshapeCollisionTester::buildShape()
{
	if (_points.size() < 1) return;
	if (_points.size() > 2) addLine(_points.back(), _points[0]);

	PolyShape shape(_points);
	Vec2 midpoint = shape.CalculateMidPoint();
	shape.Translate(-midpoint);
	GameObject* polyObject = new GameObject(midpoint);
	RigidBody* rb = new RigidBody(shape);
	polyObject->AddComponent(rb);
	rb->bounciness = 1.0f;

	ImageGameObject* circleImage = new ImageGameObject("Debug/Redcircle.png");
	circleImage->centered = true;
	circleImage->SetSize(2.0f, 2.0f);
	polyObject->AddChild(circleImage);

	for (ImageGameObject* gameObject : _display) polyObject->AddChild(gameObject);

	AddChild(polyObject);

	_current = rb;

	_display.clear();
	_points.clear();
}

void PolyshapeCollisionTester::onLoad()
{
	PhysicsObject* box = new PhysicsObject(
		PolyShape::Rectangle(Vec2(1.0f, 1.0f), sceneManager->GetGame()->GetWitdth()/2.0f, sceneManager->GetGame()->GetHeight()/2.0f).Invert()
	);
	box->ShowCollider();
	AddChild(box);

	box->collider->bounciness = 1.0f;
	box->SetLocalScale(1.95f);
}

void PolyshapeCollisionTester::addPoint(const Vec2 pPos)
{
	_points.push_back(pPos);
	ImageGameObject* circleImage = new ImageGameObject("Debug/Redcircle.png", pPos);
	circleImage->centered = true;
	circleImage->SetSize(2.0f, 2.0f);
	_display.push_back(circleImage);
	AddChild(circleImage);

	unsigned int count = _points.size();
	if (count < 2)  return;

	addLine(_points[count - 2], pPos);
}

void PolyshapeCollisionTester::addLine(const Vec2& pStart, const Vec2& pEnd)
{
	Vec2 lineVec = pEnd - pStart;
	Vec2 middle = lineVec / 2.0f + pStart;

	ImageGameObject* lineImage = new ImageGameObject("Debug/Greensquare.png", middle);
	lineImage->centered = true;
	lineImage->SetLocalRotation(lineVec.GetAngleRadians());
	lineImage->SetSize(lineVec.Length(), 1.0f);
	_display.push_back(lineImage);
	AddChild(lineImage);
}
