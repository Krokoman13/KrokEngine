#pragma once
#include "RenderLayer.hpp"
#include "Core/Window/Window.hpp"
#include "ResourceManager/ResourceCache/ResourceCache.hpp"

class Renderer
{
private:
	Window& m_window;

	std::vector<RenderLayer> m_renderLayers;

public:
	Renderer(Window& a_window);
	~Renderer();

	void Render();

	void Add(const std::vector<GameObject*>& a_newlyAdded);
	void Remove(const std::vector<std::unique_ptr<GameObject>>& a_toDestroy);

	void CheckAndFix();

private :
	void add(Renderable* a_renderable);
	void remove(const Renderable* a_renderable);

	void render();
};

