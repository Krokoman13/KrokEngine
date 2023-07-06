#include "GravityTest.hpp"
#include "Ball.hpp"
#include "PhysicsLine.hpp"

GravityTest::GravityTest() : PhysicsScene("GravityTest")
{
	_line = nullptr;
	_current = nullptr;
	_startPoint = Vec2();

	_resistanceCoefficient = 0.01f;
	_physicsSpeed = 10.0f;
}

void GravityTest::onLoad()
{
	PhysicsObject* box = new PhysicsObject(
		PolyShape::Rectangle(Vec2(1.0f, 1.0f), sceneManager->GetGame()->GetWitdth() / 2.0f, sceneManager->GetGame()->GetHeight() / 2.0f).Invert()
	);
	box->ShowCollider();
	AddChild(box);

	box->SetLocalScale(1.95f);

	_line = nullptr;
	_current = nullptr;
}

void GravityTest::update()
{
	if (_current)
	{
		if (Input::WentDown(sf::Mouse::Left))
		{
			_current->hasGravity = true;
			_current = nullptr;
			return;
		}

		_current->GetGameObject()->SetGlobalPosition(Input::mousePosition);
		float rotateSpeed = 0.01f;
		if (Input::IsPressed(sf::Keyboard::A)) _current->GetGameObject()->identity.Rotate(-rotateSpeed);
		else if (Input::IsPressed(sf::Keyboard::D)) _current->GetGameObject()->identity.Rotate(rotateSpeed);
		else if (Input::IsPressed(sf::Keyboard::W)) _current->GetGameObject()->identity.Scale(Vec2(1.1f, 1.1f));
		else if (Input::IsPressed(sf::Keyboard::S)) _current->GetGameObject()->identity.Scale(Vec2(0.9f, 0.9f));
		return;
	}

	if (Input::IsPressed(sf::Mouse::Right))
	{
		if (!_line)
		{
			_startPoint = Input::mousePosition;
			_line = createLine(_startPoint, _startPoint + Vec2(100, 100));
			AddChild(_line);
		}

		updateLine();
	}

	if (Input::WentUp(sf::Mouse::Right))
	{
		RemoveChild(_line);
		AddChild(new PhysicsLine(_startPoint, Input::mousePosition));
		_line = nullptr;
	}

	if (Input::WentDown(sf::Keyboard::B))
	{
		Ball* ball = new Ball(Vec2());
		AddChild(ball);
		_current = ball->rb;
		return;
	}

	if (Input::WentDown(sf::Keyboard::Num2)) build(2);
	else if (Input::WentDown(sf::Keyboard::Num3)) build(3);
	else if (Input::WentDown(sf::Keyboard::Num4)) build(4);
	else if (Input::WentDown(sf::Keyboard::Num5)) build(5);
	else if (Input::WentDown(sf::Keyboard::Num6)) build(5);
}

void GravityTest::build(unsigned int pI)
{
	PolyShape shape = PolyShape::SymetricShape(pI, 100.0f);
	RigidBody* rb = new RigidBody(shape);
	GameObject* gmObject = new GameObject("Polyshape");
	gmObject->AddComponent(rb);

	_current = rb;
	addLinesTo(gmObject, shape);
	AddChild(gmObject);
}

void GravityTest::addLinesTo(GameObject* pGameObject, const std::vector<Vec2>& pPoints)
{
	for (unsigned int i = 1; i < pPoints.size(); i++)
	{
		pGameObject->AddChild(createLine(pPoints[i - 1], pPoints[i]));
	}

	pGameObject->AddChild(createLine(pPoints.front(), pPoints.back()));
}

ImageGameObject* GravityTest::createLine(const Vec2& pStart, const Vec2& pEnd)
{
	const Vec2 lineVec = pEnd - pStart;
	const Vec2 middle = lineVec / 2.0f + pStart;

	ImageGameObject* lineImage = new ImageGameObject("Debug/Greensquare.png", middle);
	lineImage->centered = true;
	lineImage->SetGlobalRotation(lineVec.GetAngleRadians());
	lineImage->SetSize(lineVec.Length(), 1.0f);
	return lineImage;
}

void GravityTest::updateLine()
{
	const Vec2 lineVec = Input::mousePosition - _startPoint;
	const Vec2 middle = lineVec / 2.0f + _startPoint;

	//_line->SetGlobalMatrix(_line->GetGlobalMatrix());
	_line->SetWidth(lineVec.Length());
	_line->SetGlobalPosition(middle);
	_line->SetGlobalRotation(lineVec.GetAngleRadians());
}
