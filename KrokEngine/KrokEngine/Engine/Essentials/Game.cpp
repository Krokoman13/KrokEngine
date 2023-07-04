#include <iostream>
#include "Game.hpp"
#include<windows.h>
#include <SFML/Graphics.hpp>

Game::Game(std::string name, unsigned int width, unsigned int height, unsigned int targetFPS) 
	: SceneManager(this), EventHandeler(_renderWindow), _renderer(_renderWindow), _updateManger()
{
	_renderWindow.create(sf::VideoMode(width, height), name, sf::Style::Titlebar | sf::Style::Close);
	_updateManger.SetRenderer(_renderer);

	std::cout << "Game initialized.\n";

	srand((unsigned int)time(NULL));
}

Game::~Game()
{
}

void Game::Run()
{
	sf::Event event;
	sf::Clock timer;

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
	if (!(Input::IsPressed(sf::Keyboard::LControl) || Input::IsPressed(sf::Keyboard::RControl))) return;

	if (Input::WentDown(sf::Keyboard::R)) ReloadCurrentScene();
	else if (Input::WentDown(sf::Keyboard::Left)) GoToPreviousScene();
	else if (Input::WentDown(sf::Keyboard::Right)) GoToNextScene();
}
