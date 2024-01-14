#pragma once
#include <vector>
#include <iostream>

struct RenderLayer
{
	int layer = -1;
	std::vector<Drawable*> drawables;

	RenderLayer(int layer)
	{
		this->layer = layer;

		std::cout << "New layer created: " << this->layer << ".\n";
	}

	RenderLayer(int layer, const std::vector<Drawable*>& sprites) : RenderLayer(layer)
	{
		this->drawables.insert(this->drawables.end(), sprites.begin(), sprites.end());
	}

	RenderLayer(int layer, Drawable* sprite) : RenderLayer(layer)
	{
		this->drawables.push_back(sprite);
	}

	void Add(const std::vector<Drawable*>& toAdd)
	{
		this->drawables.insert(this->drawables.end(), toAdd.begin(), toAdd.end());
	}

	void Add(Drawable* toAdd)
	{
		this->drawables.push_back(toAdd);
	}
};

