#include "PhysicsScene.hpp"
#include "../../Core/SceneManager/Scene.hpp"
#include "../../Essentials/Game.hpp"


void PhysicsScene::PhysicsUpdate(Scene* pScene)
{
	handleDestroyed(pScene->ToDestroy());
	load(pScene->ToLoad());

	_cycleSpeed = _physicsSpeed * sceneManager->GetGame()->deltaSeconds;

	calculateVelocities();
	moveRidgids();
}

void PhysicsScene::load(const std::vector<GameObject*>& toLoad)
{
	for (GameObject* gameObject : toLoad)
	{
		RigidBody* rb;
		if (gameObject->TryGetComponent<RigidBody>(rb))
		{
			_rigidObjects.push_back(rb);
		}

		TriggerColliderComponent* tc;
		if (gameObject->TryGetComponent<TriggerColliderComponent>(tc))
		{
			_triggerObjects.push_back(tc);
		}

		ColliderComponent* col;
		if (gameObject->TryGetComponent<ColliderComponent>(col))
		{
			_staticObjects.push_back(col);
		}
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
	for (unsigned int i = 0; i < _rigidObjects.size(); i++)
	{
		if (component == _rigidObjects[i])
		{
			_rigidObjects.erase(_rigidObjects.begin() + i);
			return;
		}
	}

	for (unsigned int i = 0; i < _triggerObjects.size(); i++)
	{
		if (component == _triggerObjects[i])
		{
			_triggerObjects.erase(_triggerObjects.begin() + i);
			return;
		}
	}

	for (unsigned int i = 0; i < _staticObjects.size(); i++)
	{
		if (component == _staticObjects[i])
		{
			_staticObjects.erase(_staticObjects.begin() + i);
			return;
		}
	}
}

void PhysicsScene::moveRidgids(float pMultiplier)
{
	CollisionInfo shortest;

	for (unsigned int i = 0; i < _rigidObjects.size(); i++)
	{
		CollisionInfo info = moveRigid(_rigidObjects[i]);

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

void PhysicsScene::calculateVelocities()
{
	for (unsigned int i = 0; i < _rigidObjects.size(); i++)
	{
		RigidBody* rigidBody = _rigidObjects[i];
		GameObject* gameObject = rigidBody->GetGameObject();

		rigidBody->acceleration = Vec2(0, 9.81f);
		rigidBody->velocity += rigidBody->acceleration * _cycleSpeed;
		rigidBody->acceleration = Vec2();
	}
}

void PhysicsScene::applyVelocities(float pMultiplier)
{
	for (unsigned int i = 0; i < _rigidObjects.size(); i++)
	{
		RigidBody* rigidBody = _rigidObjects[i];
		GameObject* gameObject = rigidBody->GetGameObject();

		Vec2 translation = rigidBody->velocity * _cycleSpeed * pMultiplier;
		gameObject->identity.Translate(translation);
	}
}

CollisionInfo PhysicsScene::moveRigid(RigidBody* pRigidBody, float pMultiplier)
{
	Vec2 desiredTranslation = pRigidBody->velocity * _cycleSpeed * pMultiplier;

	CollisionInfo shortest;

	for (unsigned int i = 0; i < _staticObjects.size(); i++)
	{
		ColliderComponent* staticCollider = _staticObjects[i];
		CollisionInfo info = getCollision(pRigidBody, staticCollider, desiredTranslation);

		if (info.TOI < shortest.TOI)
		{
			info.aRigidBody = pRigidBody;
			shortest = info;
		}
	}

	return shortest;
}

CollisionInfo PhysicsScene::getCollision(RigidBody* pRigidBody, ColliderComponent* pStaticCollider, Vec2& desiredTranslation)
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
