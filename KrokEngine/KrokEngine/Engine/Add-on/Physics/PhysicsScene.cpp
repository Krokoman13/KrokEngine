#include "PhysicsScene.hpp"
#include "../../Core/SceneManager/Scene.hpp"
#include "../../Essentials/Game.hpp"
#include "../../Core/Input/Input.hpp"

void PhysicsScene::PhysicsUpdate()
{
	Game* game = sceneManager->GetGame();
	
	if (game->devControls && Input::IsPressed(Keyboard::Key::Space) && !Input::WentDown(Keyboard::Key::Right))
	{
		_cycleSpeed = 0.0f;
	}
	else _cycleSpeed = _physicsSpeed * Time::DeltaTimeSeconds();

	calculateVelocities();
	checkRigids();
}

std::vector<Collider*> PhysicsScene::OverLayCircle(GameObject* a_source, const float a_radius, const Vec2 a_offset)
{
	std::vector<Collider*> outp;
	CircleCollider circle = CircleCollider(a_radius, a_offset);
	circle.SetParent(a_source);

	for (ColliderComponent* colliderComp : _staticObjects) overLayCircle(outp, colliderComp, &circle);
	for (TriggerColliderComponent* colliderComp : _triggerObjects) overLayCircle(outp, colliderComp, &circle);
	for (RigidBody* colliderComp : _rigidObjects) overLayCircle(outp, colliderComp, &circle);

	return outp;
}

void PhysicsScene::SetPhyicsSpeed(float a_speed)
{
	if (a_speed < 0) a_speed = 0.f;
	_physicsSpeed = a_speed;
}


void PhysicsScene::overLayCircle(std::vector<Collider*>& a_isOverlaying, ColliderComponent* a_toCheck, const CircleCollider* a_circleCollider) {
	for (CircleCollider* circle : a_toCheck->GetCircles()) {
		const float r1 = a_circleCollider->GetRadius();
		const float r2 = circle->GetRadius();
		const Vec2 p1 = a_circleCollider->GetCenter();
		const Vec2 p2 = circle->GetCenter();

		const Vec2 diffrence = p1 - p2;     //Relative position

		if (diffrence.Length() <= (r1 + r2)) {
			a_isOverlaying.push_back(circle);
		}
	}

	for (LineCollider* line : a_toCheck->GetLines()) {
		Vec2 p1 = line->GetStart();
		Vec2 p2 = line->GetEnd();

		Vec2 c = a_circleCollider->GetCenter();
		float r = a_circleCollider->GetRadius();

		Vec2 lineDir = p2 - p1; // Corrected direction of the line
		Vec2 lineCenter = (p1 + p2) / 2.0f; // midpoint of the line segment
		Vec2 dirToCircleCenter = c - lineCenter; // direction from line center to circle center

		float t = dirToCircleCenter.Dot(lineDir) / lineDir.Dot(lineDir); // projection scalar

		Vec2 closestPointOnLine;
		if (t < 0.0f) {
			closestPointOnLine = p1;
		}
		else if (t > 1.0f) {
			closestPointOnLine = p2;
		}
		else {
			closestPointOnLine = lineCenter;
		}

		float distance = (closestPointOnLine - c).Length();

		if (distance <= r) {
			a_isOverlaying.push_back(line);
		}
	}
}


void PhysicsScene::load(const std::vector<GameObject*>& toLoad)
{
	for (unsigned int i = 0; i < toLoad.size(); i++)
	{
		const std::vector<std::unique_ptr<Component>>& components = toLoad[i]->Components();

		for (unsigned int j = 0; j < components.size(); j++)
		{
			load(components[j].get());
		}
	}
}

void PhysicsScene::load(Component* pComponent)
{
	if (typeid(*pComponent) == typeid(RigidBody))
	{
		RigidBody* rb = dynamic_cast<RigidBody*>(pComponent);
		_rigidObjects.push_back(rb);
		return;
	}

	if (typeid(*pComponent) == typeid(TriggerColliderComponent))
	{
		TriggerColliderComponent* tc = dynamic_cast<TriggerColliderComponent*>(pComponent);
		_triggerObjects.push_back(tc);
		return;
	}

	if (typeid(*pComponent) == typeid(ColliderComponent))
	{
		ColliderComponent* stat = dynamic_cast<ColliderComponent*>(pComponent);
		_staticObjects.push_back(stat);
		return;
	}
}

void PhysicsScene::handleDestroyed(const std::vector<std::unique_ptr<GameObject>>& pToDestroy)
{
	for (unsigned int i = 0; i < pToDestroy.size(); i++)
	{
		const std::vector<std::unique_ptr<Component>>& components = pToDestroy[i]->Components();

		for (unsigned int j = 0; j < components.size(); j++)
		{
			handleDestroyed(components[j].get());
		}
	}
}

void PhysicsScene::handleDestroyed(Component* component)
{
	if (typeid(*component) == typeid(RigidBody))
	{
		for (unsigned int i = 0; i < _rigidObjects.size(); i++)
		{
			if (component == _rigidObjects[i])
			{
				_rigidObjects.erase(_rigidObjects.begin() + i);
				return;
			}
		}

		return;
	}

	if (typeid(*component) == typeid(TriggerColliderComponent))
	{
		for (unsigned int i = 0; i < _triggerObjects.size(); i++)
		{
			if (component == _triggerObjects[i])
			{
				_triggerObjects.erase(_triggerObjects.begin() + i);
				return;
			}
		}

		return;
	}

	if (typeid(*component) == typeid(ColliderComponent))
	{
		for (unsigned int i = 0; i < _staticObjects.size(); i++)
		{
			if (component == _staticObjects[i])
			{
				_staticObjects.erase(_staticObjects.begin() + i);
				return;
			}
		}

		return;
	}
}

void PhysicsScene::checkRigids(const float pMultiplier)
{
	CollisionInfo shortest;

	for (unsigned int i = 0; i < _rigidObjects.size(); i++)
	{
		CollisionInfo info = checkRigid(_rigidObjects[i], pMultiplier, i);

		if (info.TOI < 0.1f)
		{
			resolveCollision(info);
			continue;
		}

		if (info.TOI < shortest.TOI)
		{
			shortest = info;
		}
	}

	if (shortest.TOI < 1.0f)
	{
		const float relativeTOI = shortest.TOI * pMultiplier;
		//std::cout << relativeTOI << '\n';
		applyVelocities(shortest.TOI);

		resolveCollision(shortest);

		const float newMultiplier = pMultiplier - relativeTOI;

		if (newMultiplier >= _minToi)
		{
			checkRigids(newMultiplier);
			return;
		}
		return;
	}

	//if (pMultiplier < 1.0f) std::cout << '\n';
	applyVelocities(pMultiplier);
}

void PhysicsScene::calculateVelocities()
{
	for (unsigned int i = 0; i < _rigidObjects.size(); i++)
	{
		RigidBody* rigidBody = _rigidObjects[i];

		if (!rigidBody->IsActive()) continue;

		if (rigidBody->hasGravity) rigidBody->acceleration += _gravity;
		rigidBody->velocity += rigidBody->acceleration * _cycleSpeed;

		Vec2 resistanceForce = -rigidBody->velocity * _resistanceCoefficient;
		rigidBody->velocity += resistanceForce * _cycleSpeed;

		if (rigidBody->velocity.Length() < _resistanceCoefficient) rigidBody->velocity = Vec2();

		rigidBody->acceleration = Vec2();
	}
}

void PhysicsScene::applyVelocities(const float pMultiplier)
{
	for (unsigned int i = 0; i < _rigidObjects.size(); i++)
	{
		RigidBody* rigidBody = _rigidObjects[i];
		if (!rigidBody->IsActive()) continue;

		GameObject* gameObject = rigidBody->GetGameObject();

		const Vec2 translation = rigidBody->velocity * _cycleSpeed * pMultiplier;

		for (unsigned int i = 0; i < _triggerObjects.size(); i++)
		{
			TriggerColliderComponent* tCollider = _triggerObjects[i];
			if (!tCollider->IsActive()) continue;

			CollisionInfo info = getCollision(rigidBody, translation, tCollider);

			if (info.TOI < pMultiplier)
			{
				tCollider->CollidesWith(info.collider1);
			}
		}

		gameObject->GlobalTranslate(translation);
	}
}

void PhysicsScene::resolveCollision(const CollisionInfo& pCollision)
{
	//pCollision.rigidBody1->GetGameObject()->GlobalTranslate(pCollision.trans1 * 2.f);
	pCollision.rigidBody1->CollidesWith(pCollision.collider2);

	if (pCollision.rigidBody2) {
		resolveCollision(pCollision.rigidBody1, pCollision.rigidBody2, pCollision.normal);
		//pCollision.rigidBody1->GetGameObject()->GlobalTranslate(pCollision.trans2 * 2.f);
	}
	else {
		resolveCollision(pCollision.rigidBody1, pCollision.collider2, pCollision.normal);
	}
}

void PhysicsScene::resolveCollision(RigidBody* pRigidBody1, RigidBody* pRigidBody2, const Vec2& pNormal)
{
	const float c = calculateBounciness(pRigidBody1, pRigidBody2);

	const Vec2 v1 = pRigidBody1->velocity;
	const Vec2 v2 = pRigidBody2->velocity;
	const float m1 = pRigidBody1->weight;
	const float m2 = pRigidBody2->weight;

	const Vec2 u = (m1 * v1 + m2 * v2) / (m1 + m2);
	pRigidBody1->velocity = (v1 - (1 + c) * ((v1 - u).Dot(pNormal)) * pNormal);
	pRigidBody2->velocity = (v2 - (1 + c) * ((v2 - u).Dot(pNormal)) * pNormal);
}

void PhysicsScene::resolveCollision(RigidBody* pRigidBody, Collider* pCol, const Vec2& pNormal)
{
	float bounciness = calculateBounciness(pRigidBody, pCol->GetColliderComponent());
	pRigidBody->velocity.Reflect(pNormal, bounciness);
}

float PhysicsScene::calculateBounciness(ColliderComponent* pA, ColliderComponent* pB)
{
	float outp = pA->bounciness;
	outp += pB->bounciness;
	outp /= 2.0f;

	if (outp < 0) outp = 0;

	return outp;
}

CollisionInfo PhysicsScene::checkRigid(RigidBody* pRigidBody, const float pMultiplier, unsigned int pChecked)
{
	CollisionInfo shortest;
	
	if (!pRigidBody->IsActive()) return shortest;

	const Vec2 desiredTranslation = pRigidBody->velocity * _cycleSpeed * pMultiplier;

	for (unsigned int i = 0; i < _staticObjects.size(); i++)
	{
		ColliderComponent* staticCollider = _staticObjects[i];
		if (!staticCollider->IsActive()) continue;

		CollisionInfo info = getCollision(pRigidBody, desiredTranslation, staticCollider);

		if (info.TOI < shortest.TOI)
		{
			info.rigidBody1 = pRigidBody;
			shortest = info;
		}
	}

	for (unsigned int i = pChecked + 1; i < _rigidObjects.size(); i++)
	{
		RigidBody* otherRigid = _rigidObjects[i];
		if (!otherRigid->IsActive()) continue;

		const Vec2 otherDesiredTranslation = otherRigid->velocity * _cycleSpeed * pMultiplier;
		CollisionInfo info = getCollision(pRigidBody, desiredTranslation, otherRigid, otherDesiredTranslation, _minToi);

		if (info.TOI < shortest.TOI)
		{
			info.rigidBody1 = pRigidBody;
			info.rigidBody2 = otherRigid;
			shortest = info;
		}
	}

	return shortest;
}

CollisionInfo PhysicsScene::getCollision(RigidBody* pRigidBody1, const Vec2& pDesTran1, RigidBody* pRigidBody2, const Vec2& pDestran2, const float minToi)
{
	CollisionInfo shortest;

	for (CircleCollider* circle : pRigidBody1->GetCircles())
	{
		for (CircleCollider* circle2 : pRigidBody2->GetCircles())
		{
			CollisionInfo info = CollisionCalculator::CalculateCollision(circle, pDesTran1, circle2, pDestran2);

			if (info.TOI < minToi)
			{
				resolveCollision(pRigidBody1, pRigidBody2, info.normal);
				//pRigidBody1->GetGameObject()->GlobalTranslate(info.trans1);
				//pRigidBody2->GetGameObject()->GlobalTranslate(info.trans2);
				//pRigidBody1->velocity = pRigidBody2->velocity = Vec2();
				continue;
			}

			if (info.TOI < shortest.TOI)
			{
				shortest = info;
			}
		}
	}

	for (CircleCollider* circle : pRigidBody1->GetCircles())
	{
		for (LineCollider* line : pRigidBody2->GetLines())
		{
			CollisionInfo info = CollisionCalculator::CalculateCollision(circle, pDesTran1, line, pDestran2);

			if (info.TOI < minToi)
			{
				resolveCollision(pRigidBody1, pRigidBody2, info.normal);
				//pRigidBody1->GetGameObject()->GlobalTranslate(info.trans1);
				//pRigidBody2->GetGameObject()->GlobalTranslate(info.trans2);
				//pRigidBody1->velocity = pRigidBody2->velocity = Vec2();
				continue;
			}

			if (info.TOI < shortest.TOI)
			{
				shortest = info;
			}
		}
	}

	for (LineCollider* line : pRigidBody1->GetLines())
	{
		for (CircleCollider* circle : pRigidBody2->GetCircles())
		{
			CollisionInfo info = CollisionCalculator::CalculateCollision(circle, pDestran2, line, pDesTran1);

			if (info.TOI < minToi)
			{
				resolveCollision(pRigidBody1, pRigidBody2, info.normal);
				//pRigidBody1->GetGameObject()->GlobalTranslate(info.trans1);
				//pRigidBody2->GetGameObject()->GlobalTranslate(info.trans2);
				//pRigidBody1->velocity = pRigidBody2->velocity = Vec2();
				continue;
			}

			if (info.TOI < shortest.TOI)
			{
				shortest = info;
			}
		}
	}

	return shortest;
}

void PhysicsScene::clearScene()
{
	_staticObjects.clear();
	_rigidObjects.clear();
	_triggerObjects.clear();

	Scene::clearScene();
}

CollisionInfo PhysicsScene::getCollision(RigidBody* pRigidBody, const Vec2& pDesiredTranslation, ColliderComponent* pStaticCollider)
{
	CollisionInfo shortest;

	for (CircleCollider* circle : pRigidBody->GetCircles())
	{
		for (LineCollider* line : pStaticCollider->GetLines())
		{
			CollisionInfo info = CollisionCalculator::CalculateCollision(circle, pDesiredTranslation, line);

			if (info.TOI < shortest.TOI)
			{
				shortest = info;
			}
		}

		for (CircleCollider* circle2 : pStaticCollider->GetCircles())
		{
			CollisionInfo info = CollisionCalculator::CalculateCollision(circle, pDesiredTranslation, circle2);

			if (info.TOI < shortest.TOI)
			{
				shortest = info;
			}
		}
	}

	for (LineCollider* line : pRigidBody->GetLines())
	{
		for (CircleCollider* circle : pStaticCollider->GetCircles())
		{
			CollisionInfo info = CollisionCalculator::CalculateCollision(circle, Vec2(), line, pDesiredTranslation);

			if (info.TOI < shortest.TOI)
			{
				shortest = info;
			}
		}
	}

	return shortest;
}
