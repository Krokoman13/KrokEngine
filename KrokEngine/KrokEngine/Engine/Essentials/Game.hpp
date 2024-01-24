#pragma once
#include <string>
#include <chrono>
#include "../Core/SceneManager/SceneManager.hpp"
#include "../Core/Events/EventHandeler/EventHandeler.hpp"
#include "../Core/Graphics/Core/Window/Window.hpp"
#include "../Core/Graphics/Renderer.hpp"
#include "../Core/UpdateManager/UpdateManager.hpp"

class Game 
	: public SceneManager
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
	EventHandeler _eventManager;

	Window _window;

	std::chrono::steady_clock::time_point t1 = std::chrono::high_resolution_clock::now();

	void handleDevControls();
};

