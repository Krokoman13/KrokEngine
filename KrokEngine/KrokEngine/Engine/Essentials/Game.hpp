#pragma once
#include <string>
#include "../Core/SceneManager/SceneManager.hpp"
#include "../Core/EventHandeler/EventHandeler.hpp"
#include "../Core/Graphics/Renderer.hpp"
#include "../Core/UpdateManager/UpdateManager.hpp"

class Game 
	: public SceneManager, public EventHandeler
{
public:
	Game(const std::string& pName, const unsigned int pWidth, const unsigned int pHeight, const unsigned int pTargetFPS);
	virtual ~Game();

	void Run();

	unsigned int GetWitdth();
	unsigned int GetHeight();

	float deltaSeconds = 0;
	bool devControls = false;

private:
	Renderer _renderer;
	UpdateManager _updateManger;

	sf::RenderWindow _renderWindow;

	void handleDevControls();
};

