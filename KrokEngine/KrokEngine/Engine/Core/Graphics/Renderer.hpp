#pragma once
#include "RenderLayer.hpp"

class Scene;
class GameObject;

class Renderer
{
public :
	Renderer(sf::RenderWindow& _window);
	~Renderer();

	void Render();

	void ToRender(const std::vector<sf::Drawable*>& sprites, int layer);
	void ToRender(sf::Drawable* sprite, int layer);

private :
	std::vector<GameObject*> _toRender;

	void render();
	sf::RenderWindow* _window;
	std::vector<RenderLayer> _renderLayers;
};

