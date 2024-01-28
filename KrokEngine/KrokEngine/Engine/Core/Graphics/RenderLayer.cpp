#include "RenderLayer.hpp"
#include "Core/Window/Renderable.hpp"

RenderLayer::RenderLayer(int a_layer)
{
	layer = a_layer;

	//std::cout << "New layer created: " << layer << ".\n";
}

RenderLayer::RenderLayer(int a_layer, const std::vector<Renderable*>& a_sprites) : RenderLayer(a_layer)
{
	renderables.insert(renderables.end(), a_sprites.begin(), a_sprites.end());
}

RenderLayer::RenderLayer(int a_layer, Renderable* a_sprite) : RenderLayer(a_layer)
{
	renderables.push_back(a_sprite);
}

void RenderLayer::Add(const std::vector<Renderable*>& a_toAdd)
{
	renderables.insert(renderables.end(), a_toAdd.begin(), a_toAdd.end());
}

void RenderLayer::Add(Renderable* a_toAdd)
{
	renderables.push_back(a_toAdd);
}