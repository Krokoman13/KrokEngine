#pragma once
#include "PhysicsManager/PhysicsManager.hpp"
#include "../../Core/SceneManager/SceneManager.hpp"
#include "../../Essentials/Game.hpp"

class PhysicsScene : public Scene
{
private:
	PhysicsManager manager;

public:
	using Scene::Scene;

	virtual void HandleObjectsInScene() override
	{
		manager.cycleSpeed = manager.physicsSpeed * sceneManager->GetGame()->deltaSeconds;
		manager.Update(this);
		Scene::HandleObjectsInScene();
	}
};

