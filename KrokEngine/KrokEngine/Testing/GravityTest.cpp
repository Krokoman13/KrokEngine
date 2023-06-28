#include "GravityTest.hpp"

GravityTest::GravityTest() : PhysicsScene("GravityTest")
{
	_current = nullptr;
}

void GravityTest::onLoad()
{
	PhysicsObject* box = new PhysicsObject(
		PolyShape::Rectangle(Vec2(1.0f, 1.0f), sceneManager->GetGame()->GetWitdth() / 2.0f, sceneManager->GetGame()->GetHeight() / 2.0f).Invert()
	);
	box->ShowCollider();
	AddChild(box);

	box->collider->bounciness = 1.0f;
	box->SetLocalScale(1.95f, 1.95f);
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
		float rotateSpeed = 0.1f;
		if (Input::IsPressed(sf::Keyboard::A)) _current->GetGameObject()->identity.Rotate(-rotateSpeed);
		else if (Input::IsPressed(sf::Keyboard::D)) _current->GetGameObject()->identity.Rotate(rotateSpeed);
		return;
	}

	if (Input::WentDown(sf::Keyboard::Num1)) build(1);
	else if (Input::WentDown(sf::Keyboard::Num2)) build(2);
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

GameObject* GravityTest::createLine(const Vec2& pStart, const Vec2& pEnd)
{
	Vec2 lineVec = pEnd - pStart;
	Vec2 middle = lineVec / 2.0f + pStart;

	ImageGameObject* lineImage = new ImageGameObject("Debug/Greensquare.png", middle);
	lineImage->centered = true;
	lineImage->SetLocalRotation(lineVec.GetAngleRadians());
	lineImage->SetSize(lineVec.Length(), 1.0f);
	return lineImage;
}
