#pragma once
#include <vector>
#include <iostream>

class Renderable;

struct RenderLayer
{
	int layer;
	std::vector<Renderable*> renderables;

	RenderLayer(int a_layer);

	RenderLayer(int a_layer, const std::vector<Renderable*>& a_sprites);

	RenderLayer(int a_layer, Renderable* a_sprite);

	void Add(const std::vector<Renderable*>& a_toAdd);

	void Add(Renderable* a_toAdd);
};

