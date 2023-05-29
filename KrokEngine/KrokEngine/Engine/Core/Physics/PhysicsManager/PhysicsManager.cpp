#include "PhysicsManager.hpp"
#include "../../SceneManager/Scene.hpp"
#include "../../../Essentials/Game.hpp"
//#include "../../../Essentials/Component.hpp"

PhysicsManager::PhysicsManager(Game* pGame)
{
	_game = pGame;
	_cycleSpeed = _physicsSpeed;
}

void PhysicsManager::Update(Scene* pScene)
{
	_cycleSpeed = _physicsSpeed * _game->deltaSeconds;

	cleanTriggers();
	cleanStatics();
	cleanRigids();

	Load(pScene->ToLoad());

	calculateVelocities();
	moveRidgids();
}

void PhysicsManager::Load(const std::vector<GmObjctPtr>& toLoad)
{
	for (GmObjctPtr gameObject : toLoad)
	{
		RigidBody* rb;
		if (gameObject->TryGetComponent(rb))
		{
			_rigidObjects.push_back(rb);
		}

		TriggerColliderComponent* tc;
		if (gameObject->TryGetComponent(tc))
		{
			_triggerObjects.push_back(tc);
		}

		ColliderComponent* col;
		if (gameObject->TryGetComponent(col))
		{
			_staticObjects.push_back(col);
		}
	}
}

void PhysicsManager::cleanTriggers()
{
	unsigned int i = 0;

	while (i < _triggerObjects.size())
	{
		TriggerColliderComponent* triggerObject = _triggerObjects[i];

		if (triggerObject == nullptr)
		{
			_triggerObjects.erase(_triggerObjects.begin() + i);
			continue;
		}

		i++;
	}
}

void PhysicsManager::cleanStatics()
{
	unsigned int i = 0;

	while (i < _staticObjects.size())
	{
		ColliderComponent* staticObject = _staticObjects[i];

		if (staticObject == nullptr)
		{
			_staticObjects.erase(_staticObjects.begin() + i);
			continue;
		}

		i++;
	}
}

void PhysicsManager::cleanRigids()
{
	unsigned int i = 0;

	while (i < _rigidObjects.size())
	{
		RigidBody* rigidObject = _rigidObjects[i];

		if (rigidObject == nullptr)
		{
			_rigidObjects.erase(_rigidObjects.begin() + i);
			continue;
		}

		i++;
	}
}

void PhysicsManager::moveRidgids(float pMultiplier)
{
	CollisionInfo shortest;

	for (RigidBody* rigidBody : _rigidObjects)
	{
		CollisionInfo info = moveRigid(rigidBody);
		
		if (info.TOI < shortest.TOI)
		{
			shortest = info;
		}
	}

	if (shortest.TOI < 1.0f)
	{
		float relativeTOI = shortest.TOI * pMultiplier;
		applyVelocities(shortest.TOI);

		shortest.aRigidBody->velocity = shortest.aVelocity / _cycleSpeed;

		float newMultiplier = pMultiplier - relativeTOI;
		if (newMultiplier < _minToi) return;
		moveRidgids(newMultiplier);
		return;
	}

	applyVelocities(pMultiplier);
}

void PhysicsManager::calculateVelocities()
{
	for (RigidBody* rigidBody : _rigidObjects)
	{
		GameObject* gameObject = rigidBody->GetGameObject();
		rigidBody->acceleration = Vec2(0, 9.81f);
		rigidBody->velocity += rigidBody->acceleration * _cycleSpeed;
		rigidBody->acceleration = Vec2();
	}
}

void PhysicsManager::applyVelocities(float pMultiplier)
{
	for (RigidBody* rigidBody : _rigidObjects)
	{
		GameObject* gameObject = rigidBody->GetGameObject();
		Vec2 translation = rigidBody->velocity * _cycleSpeed * pMultiplier;
		gameObject->identity.Translate(translation);
	}
}

CollisionInfo PhysicsManager::moveRigid(RigidBody* pRigidBody, float pMultiplier)
{
	Vec2 desiredTranslation = pRigidBody->velocity * _cycleSpeed * pMultiplier;

	CollisionInfo shortest;

	for (ColliderComponent* staticCollider : _staticObjects)
	{
		CollisionInfo info = getCollision(pRigidBody, staticCollider, desiredTranslation);



		if (info.TOI < shortest.TOI)
		{
			info.aRigidBody = pRigidBody;
			shortest = info;
		}
	}

	return shortest;
}

CollisionInfo PhysicsManager::getCollision(RigidBody* pRigidBody, ColliderComponent* pStaticCollider, Vec2& desiredTranslation)
{
	CollisionInfo shortest;

	for (CircleCollider* circle : pRigidBody->GetCircles())
	{
		for (LineCollider* line : pStaticCollider->GetLines())
		{
			CollisionInfo info = CollisionCalculator::CalculateCollision(circle, desiredTranslation, line);

			if (info.TOI < _minToi)
			{
				pRigidBody->velocity = info.aVelocity / _cycleSpeed;
				pRigidBody->GetGameObject()->SetGlobalPosition(info.aPOI);
				continue;
			}

			if (info.TOI < shortest.TOI)
			{
				shortest = info;
			}
		}

		for (CircleCollider* circle2 : pStaticCollider->GetCircles())
		{
			CollisionInfo info = CollisionCalculator::CalculateCollision(circle, desiredTranslation, circle2);

			if (info.TOI < _minToi)
			{
				pRigidBody->velocity = info.aVelocity / _cycleSpeed;
				pRigidBody->GetGameObject()->SetGlobalPosition(info.aPOI);
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