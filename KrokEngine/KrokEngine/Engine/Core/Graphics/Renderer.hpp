#pragma once
#include "RenderLayer.hpp"
#include "../../Essentials/ManagedPtr.hpp"

class Scene;
class GameObject;

class Renderer
{
public :
	Renderer(sf::RenderWindow& _window);
	~Renderer();

	void Render(Scene* scene);

	void ToRender(const std::vector<sf::Drawable*>& sprites, int layer);
	void ToRender(sf::Drawable* sprite, int layer);

private :
	std::vector<ManagedPtr<GameObject>> _toRender;

	void render();
	sf::RenderWindow* _window;
	std::vector<RenderLayer> _renderLayers;
};

