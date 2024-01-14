#pragma once
#include "RenderLayer.hpp"

class Scene;
class GameObject;

class Renderer
{
public :
	Renderer(RenderWindow& _window);
	~Renderer();

	void Render();

	void ToRender(const std::vector<Drawable*>& sprites, int layer);
	void ToRender(Drawable* sprite, int layer);

private :
	std::vector<GameObject*> _toRender;

	void render();
	RenderWindow* _window;
	std::vector<RenderLayer> _renderLayers;
};

