#pragma once
#include <string>
#include "../Core/SceneManager/SceneManager.hpp"
#include "../Core/EventHandeler/EventHandeler.hpp"
#include "../Core/Graphics/Renderer.hpp"
#include "../Core/UpdateManager/UpdateManager.hpp"
#include "../Core/Physics/PhysicsManager/PhysicsManager.hpp"

class Game 
	: public SceneManager, public EventHandeler
{
public:
	Game(std::string name, unsigned int width, unsigned int height, unsigned int targetFPS);
	virtual ~Game();

	void Run();

	unsigned int GetWitdth();
	unsigned int GetHeight();

	float deltaSeconds = 0;

private:
	Renderer _renderer;
	UpdateManager _updateManger;
	PhysicsManager _physicsManager;

	sf::RenderWindow _renderWindow;
};

