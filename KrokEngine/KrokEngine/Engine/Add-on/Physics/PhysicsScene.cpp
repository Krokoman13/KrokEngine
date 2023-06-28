#include "PhysicsScene.hpp"
#include "../../Core/SceneManager/Scene.hpp"
#include "../../Essentials/Game.hpp"

void PhysicsScene::PhysicsUpdate()
{
	handleDestroyed(ToDestroy());
	load(ToLoad());

	_cycleSpeed = _physicsSpeed * sceneManager->GetGame()->deltaSeconds;

	calculateVelocities();
	checkRigids();
}

void PhysicsScene::load(const std::vector<GameObject*>& toLoad)
{
	for (unsigned int i = 0; i < toLoad.size(); i++)
	{
		const std::vector<std::unique_ptr<Component>>& components = toLoad[i]->GetComponents();

		for (unsigned int j = 0; j < components.size(); j++)
		{
			load(components[j].get());
		}
	}
}

void PhysicsScene::load(Component* pComponent)
{
	RigidBody* rb = dynamic_cast<RigidBody*>(pComponent);
	if (rb)
	{
		_rigidObjects.push_back(rb);
		return;
	}

	TriggerColliderComponent* tc = dynamic_cast<TriggerColliderComponent*>(pComponent);
	if (tc)
	{
		_triggerObjects.push_back(tc);
		return;
	}

	ColliderComponent* stat = dynamic_cast<ColliderComponent*>(pComponent);
	if (stat)
	{
		_staticObjects.push_back(stat);
		return;
	}
}

void PhysicsScene::handleDestroyed(const std::vector<std::unique_ptr<GameObject>>& pToDestroy)
{
	for (unsigned int i = 0; i < pToDestroy.size(); i++)
	{
		const std::vector<std::unique_ptr<Component>>& components = pToDestroy[i]->GetComponents();

		for (unsigned int j = 0; j < components.size(); j++)
		{
			handleDestroyed(components[j].get());
		}
	}
}

void PhysicsScene::handleDestroyed(Component* component)
{
	if (dynamic_cast<RigidBody*>(component))
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

	if (dynamic_cast<TriggerColliderComponent*>(component))
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

	if (dynamic_cast<ColliderComponent*>(component))
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

		if (info.TOI < shortest.TOI)
		{
			shortest = info;
		}
	}

	if (shortest.TOI < 1.0f)
	{
		const float relativeTOI = shortest.TOI * pMultiplier;
		applyVelocities(shortest.TOI);

		resolveCollision(shortest);

		const float newMultiplier = pMultiplier - relativeTOI;
		if (newMultiplier < _minToi) return;
		checkRigids(newMultiplier);
		return;
	}

	applyVelocities(pMultiplier);
}

void PhysicsScene::calculateVelocities()
{
	for (unsigned int i = 0; i < _rigidObjects.size(); i++)
	{
		RigidBody* rigidBody = _rigidObjects[i];

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
		GameObject* gameObject = rigidBody->GetGameObject();

		const Vec2 translation = rigidBody->velocity * _cycleSpeed * pMultiplier;
		gameObject->GlobalTranslate(translation);
	}
}

void PhysicsScene::resolveCollision(const CollisionInfo& pCollision)
{
	if (pCollision.rigidBody2) resolveCollision(pCollision.rigidBody1, pCollision.rigidBody2, pCollision.normal);
	else resolveCollision(pCollision.rigidBody1, pCollision.collider2, pCollision.normal);
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

	return std::abs(outp);
}

CollisionInfo PhysicsScene::checkRigid(RigidBody* pRigidBody, const float pMultiplier, unsigned int pChecked)
{
	const Vec2 desiredTranslation = pRigidBody->velocity * _cycleSpeed * pMultiplier;

	CollisionInfo shortest;

	for (unsigned int i = 0; i < _staticObjects.size(); i++)
	{
		ColliderComponent* staticCollider = _staticObjects[i];
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
		const Vec2 otherDesiredTranslation = otherRigid->velocity * _cycleSpeed * pMultiplier;
		CollisionInfo info = getCollision(pRigidBody, desiredTranslation, otherRigid, otherDesiredTranslation);

		if (info.TOI < shortest.TOI)
		{
			info.rigidBody1 = pRigidBody;
			info.rigidBody2 = otherRigid;
			shortest = info;
		}
	}

	return shortest;
}

CollisionInfo PhysicsScene::getCollision(RigidBody* pRigidBody1, const Vec2& pDesTran1, RigidBody* pRigidBody2, const Vec2& pDestran2)
{
	CollisionInfo shortest;

	for (CircleCollider* circle : pRigidBody1->GetCircles())
	{
		for (CircleCollider* circle2 : pRigidBody2->GetCircles())
		{
			CollisionInfo info = CollisionCalculator::CalculateCollision(circle, pDesTran1, circle2, pDestran2);

			if (info.TOI < _minToi)
			{
				resolveCollision(pRigidBody1, pRigidBody2, info.normal);
				pRigidBody1->GetGameObject()->GlobalTranslate(info.trans1);
				pRigidBody2->GetGameObject()->GlobalTranslate(info.trans2);
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

			if (info.TOI < _minToi)
			{
				resolveCollision(pRigidBody1, pRigidBody2, info.normal);
				pRigidBody1->GetGameObject()->GlobalTranslate(info.trans1);
				pRigidBody2->GetGameObject()->GlobalTranslate(info.trans2);
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

			if (info.TOI < _minToi)
			{
				resolveCollision(pRigidBody1, pRigidBody2, info.normal);
				pRigidBody1->GetGameObject()->GlobalTranslate(info.trans1);
				pRigidBody2->GetGameObject()->GlobalTranslate(info.trans2);
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

CollisionInfo PhysicsScene::getCollision(RigidBody* pRigidBody, const Vec2& pDesiredTranslation, ColliderComponent* pStaticCollider)
{
	CollisionInfo shortest;

	for (CircleCollider* circle : pRigidBody->GetCircles())
	{
		for (LineCollider* line : pStaticCollider->GetLines())
		{
			CollisionInfo info = CollisionCalculator::CalculateCollision(circle, pDesiredTranslation, line);

			if (info.TOI < _minToi)
			{
				resolveCollision(pRigidBody, info.collider2, info.normal);
				pRigidBody->GetGameObject()->GlobalTranslate(info.trans1);
				continue;
			}

			if (info.TOI < shortest.TOI)
			{
				shortest = info;
			}
		}

		for (CircleCollider* circle2 : pStaticCollider->GetCircles())
		{
			CollisionInfo info = CollisionCalculator::CalculateCollision(circle, pDesiredTranslation, circle2);

			if (info.TOI < _minToi)
			{
				resolveCollision(pRigidBody, info.collider2, info.normal);
				pRigidBody->GetGameObject()->GlobalTranslate(info.trans1);
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
