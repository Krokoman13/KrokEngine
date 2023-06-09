#include <iostream>
#include "Game.hpp"
#include <SFML/Graphics.hpp>

Game::Game(std::string name, unsigned int width, unsigned int height, unsigned int targetFPS) 
	: SceneManager(new Scene("StartScreen"), this), EventHandeler(_renderWindow), _renderer(_renderWindow), _updateManger()
{
	_renderWindow.create(sf::VideoMode(width, height), name, sf::Style::Titlebar | sf::Style::Close);
	_updateManger.SetRenderer(_renderer);

	std::cout << "Game initialized.\n";

	srand((unsigned int)time(NULL));
}

Game::~Game()
{
	//SceneManager::~SceneManager();
	//EventHandeler::~EventHandeler();
}

void Game::Run()
{
	sf::Event event;
	sf::Clock timer;

	while (_renderWindow.isOpen())
	{
		while (this->_renderWindow.pollEvent(event))
		{
			HandleEvent(event, GetCurrentScene()->ui);
		}

		if (!Focus()) continue;

		_updateManger.Update(GetCurrentScene());

		{
			std::vector<sf::Drawable*> drawables = GetCurrentScene()->ui->GetDrawables();
			_renderer.ToRender(drawables, INT_MAX);
		}

		_renderer.Render();
	}
}

unsigned int Game::GetWitdth()
{
	return _renderWindow.getSize().x;
}

unsigned int Game::GetHeight()
{
	return _renderWindow.getSize().x;
}