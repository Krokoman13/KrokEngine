#include <iostream>
#include "Game.hpp"
#include "../Core/Graphics/ResourceManager/ResourceManager.hpp"

Game::Game(const std::string& pName, const unsigned int pWidth, const unsigned int pHeight, const unsigned int pTargetFPS)
	: _window(pName.c_str(), pWidth, pHeight), SceneManager(this), EventHandeler(), _renderer(_window), _updateManger()
{
	std::cout << "Game initialized.\n";

	srand((unsigned int)time(NULL));
}

Game::~Game()
{
	clearAllScenes();
	_renderer.ClearCaches();
}

void Game::Run()
{
	//Event event;

	while (_window.IsOpen())
	{
		ClearButtons();
		Scene* currentScene = GetCurrentScene();
		Input::previousMousePosition = Input::mousePosition;

		//Handle Events
		//while (_renderWindow.pollEvent(event))
		//{
		//	HandleEvent(event);
		//}

		std::chrono::steady_clock::time_point t2 = std::chrono::high_resolution_clock::now();
		std::chrono::milliseconds ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
		deltaSeconds = ms_int.count() / 1000.f;
		t1 = std::chrono::high_resolution_clock::now();

		if (!Input::focus) continue;

		if (devControls) handleDevControls();

		_updateManger.Update(currentScene);

		_renderer.Add(currentScene->ToLoad());
		_renderer.Remove(currentScene->ToDestroy());
		_renderer.Render();

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
