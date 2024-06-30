#pragma once
#include <string>
#include <chrono>
#include "../Core/SceneManager/SceneManager.hpp"
#include "../Core/Events/EventHandeler/EventHandeler.hpp"
#include "../Core/Graphics/Core/Window/Window.hpp"
#include "../Core/Graphics/Renderer.hpp"
#include "../Core/UpdateManager/UpdateManager.hpp"
#include "../Util/Time.hpp"

class Game 
	: public SceneManager
{
private:
	Renderer m_renderer;
	UpdateManager m_updateManger;
	EventHandeler m_eventManager;

	Window m_window;

	std::chrono::steady_clock::time_point m_t1 = std::chrono::high_resolution_clock::now();

public:
	bool devControls = false;
	float gameSpeed = 1.0f;

public:
	Game(const std::string& pName, const unsigned int pWidth, const unsigned int pHeight, const unsigned int pTargetFPS);
	virtual ~Game();

public:
	Camera& GetCamera() { return m_window.camera; };

	void Run();

	unsigned int GetWitdth();
	unsigned int GetHeight();

private:
	void handleDevControls();
};

