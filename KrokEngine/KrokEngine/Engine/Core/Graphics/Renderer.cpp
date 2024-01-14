#include "Renderer.hpp"
#include "ImageGameObject.hpp"
#include <iostream>
#include "../SceneManager/Scene.hpp"

Renderer::Renderer(RenderWindow& window)
{
	this->_window = &window;
	this->_renderLayers.push_back(RenderLayer(0));

	if (ImageGameObject::ASSET_PATH == "") 	std::cout << "WARNING: Asset path for ImageGameObjects is not defined\n";
	std::cout << "Renderer initialized.\n";
}

Renderer::~Renderer()
{
}

void Renderer::Render()
{
	render();
}

void Renderer::render()
{
	_window->clear();

	for (RenderLayer& renderLayer : _renderLayers)
	{
		//std::cout << renderLayer.layer << ": " << renderLayer.sprites.size() << '\n';

		while (renderLayer.drawables.size() > 0)
		{
			Drawable* sprite = renderLayer.drawables[renderLayer.drawables.size() - 1];

			if (sprite != nullptr)
			{
				_window->draw(*sprite);
			}

			renderLayer.drawables.pop_back();
		}
	}

	_window->display();
}

void Renderer::ToRender(const std::vector<Drawable*>& drawables, int layer)
{
	if (drawables.size() < 1) return;
	if (layer < 0) layer = 1;

	if (layer > this->_renderLayers[this->_renderLayers.size() - 1].layer)
	{
		RenderLayer newLayer(layer, drawables);

		_renderLayers.push_back(newLayer);
		return;
	}

	for (std::vector<RenderLayer>::iterator it = _renderLayers.begin(); it != _renderLayers.end(); ++it)
	{
		if (it->layer == layer)
		{
			it->Add(drawables);
			return;
		}

		if (it->layer > layer)
		{
			RenderLayer newLayer(layer, drawables);
			_renderLayers.insert(it, newLayer);

			return;
		}
	}
}

void Renderer::ToRender(Drawable* drawable, int layer)
{
	if (layer < 0) layer = 1;

	if (layer > _renderLayers[_renderLayers.size() - 1].layer)
	{
		RenderLayer newLayer(layer, drawable);

		_renderLayers.push_back(newLayer);
		return;
	}

	for (std::vector<RenderLayer>::iterator it = _renderLayers.begin(); it != _renderLayers.end(); ++it)
	{
		if (it->layer == layer)
		{
			it->Add(drawable);
			return;
		}

		if (it->layer > layer)
		{
			RenderLayer newLayer(layer, drawable);
			_renderLayers.insert(it, newLayer);

			return;
		}
	}
}
