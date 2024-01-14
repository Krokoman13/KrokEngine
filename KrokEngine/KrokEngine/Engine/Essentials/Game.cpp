#include <iostream>
#include "Game.hpp"
#include <windows.h>

Game::Game(const std::string& pName, const unsigned int pWidth, const unsigned int pHeight, const unsigned int pTargetFPS)
	: SceneManager(this), EventHandeler(_renderWindow), _renderer(_renderWindow), _updateManger()
{
	_renderWindow.create(VideoMode(pWidth, pHeight), pName, Style::Titlebar | Style::Close);
	_updateManger.SetRenderer(_renderer);

	std::cout << "Game initialized.\n";

	srand((unsigned int)time(NULL));
}

Game::~Game()
{
}

void Game::Run()
{
	Event event;
	Clock timer;

	while (_renderWindow.isOpen())
	{
		ClearButtons();
		Scene* currentScene = GetCurrentScene();
		Input::previousMousePosition = Input::mousePosition;

		while (_renderWindow.pollEvent(event))
		{
			HandleEvent(event);
		}

		Sleep(10);
		deltaSeconds = timer.restart().asMicroseconds() / 1000000.0f;

		if (!Input::focus) continue;

		if (devControls) handleDevControls();
		_updateManger.Update(currentScene);

		_renderer.Render();
		currentScene->HandleObjectsInScene();
	}
}

unsigned int Game::GetWitdth()
{
	return _renderWindow.getSize().x;
}

unsigned int Game::GetHeight()
{
	return _renderWindow.getSize().y;
}

void Game::handleDevControls()
{
	if (!(Input::IsPressed(Keyboard::LControl) || Input::IsPressed(Keyboard::RControl))) return;

	if (Input::WentDown(Keyboard::R)) ReloadCurrentScene();
	else if (Input::WentDown(Keyboard::Left)) GoToPreviousScene();
	else if (Input::WentDown(Keyboard::Right)) GoToNextScene();
}
