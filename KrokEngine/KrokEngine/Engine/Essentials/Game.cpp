#include <iostream>
#include "Game.hpp"

#include "../Core/Graphics/ResourceManager/ResourceManager.hpp"
#include "../Core/Input/Input.hpp"

Game::Game(const std::string& pName, const unsigned int pWidth, const unsigned int pHeight, const unsigned int pTargetFPS)
	: m_window(pName.c_str(), pWidth, pHeight), SceneManager(this), m_renderer(m_window), m_updateManger()
{
	std::cout << "Game initialized.\n";

	m_eventManager.SetCallbacks(m_window);

	srand((unsigned int)time(NULL));
}

Game::~Game()
{
	clearAllScenes();
	m_renderer.ClearCaches();
}

void Game::Run()
{
	//Event event;

	while (m_window.IsOpen())
	{
		m_eventManager.UpdateEvents();
		m_window.PollEvents();

		if (IsNewScene()) {
			m_renderer.ClearAll();
			m_eventManager.ClearAll();
			_sceneIsNew = false;
		}

		Scene* currentScene = GetCurrentScene();

		std::chrono::steady_clock::time_point t2 = std::chrono::high_resolution_clock::now();
		std::chrono::milliseconds ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - m_t1);
		Time::m_deltaTimeSeconds = ms_int.count() / 1000.f * gameSpeed;
		m_t1 = std::chrono::high_resolution_clock::now();

		//if (!Input::MouseInScreen()) continue;

		if (devControls) handleDevControls();

		m_eventManager.Add(currentScene->ToLoad());
		m_eventManager.Remove(currentScene->ToDestroy());

		m_updateManger.Update(currentScene);

		m_renderer.Add(currentScene->ToLoad());
		m_renderer.Remove(currentScene->ToDestroy());
		m_renderer.Render();

		currentScene->HandleObjectsInScene();
	}
}

unsigned int Game::GetWitdth()
{
	throw std::runtime_error("Not implimented yet");;
}

unsigned int Game::GetHeight()
{
	throw std::runtime_error("Not implimented yet");;
}

void Game::handleDevControls()
{
	if (!(Input::IsPressed(Keyboard::Key::LControl) || Input::IsPressed(Keyboard::Key::RControl))) return;

	if (Input::WentDown(Keyboard::Key::R)) ReloadCurrentScene();
	else if (Input::WentDown(Keyboard::Key::Left)) GoToPreviousScene();
	else if (Input::WentDown(Keyboard::Key::Right)) GoToNextScene();
}
