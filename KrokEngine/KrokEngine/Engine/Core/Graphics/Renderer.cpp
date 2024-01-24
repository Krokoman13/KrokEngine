#include "Renderer.hpp"
#include <iostream>
#include "../SceneManager/Scene.hpp"

#include "../Graphics/ResourceManager/ResourceManager.hpp"

Renderer::Renderer(Window& a_window) : m_window(a_window), m_shaderCache(), m_bufferCache()
{
	m_renderLayers.push_back(RenderLayer(0));

	ResourceManager::pShaderCache = &m_shaderCache;
	ResourceManager::pGLBufferCache = &m_bufferCache;

	std::cout << "Renderer initialized.\n";
}

Renderer::~Renderer()
{
}

void Renderer::Render()
{
	render();
	CheckAndFix();
}

void Renderer::Add(const std::vector<GameObject*>& a_newlyAdded)
{
	for (GameObject* gameObject : a_newlyAdded)
	{
		GameObject* temp = gameObject;
		for (Renderable* renderable : temp->GetComponents<Renderable>()) add(renderable);
	}
}

void Renderer::Remove(const std::vector<std::unique_ptr<GameObject>>& a_toDestroy)
{
	for (unsigned int i = 0; i < a_toDestroy.size(); i++)
	{
		for (Renderable* renderable : a_toDestroy[i]->GetComponents<Renderable>())  remove(renderable);
	}
}

void Renderer::CheckAndFix()
{
	std::vector<Renderable*> toFix;

	for (RenderLayer& renderLayer : m_renderLayers)
	{
		for (Renderable* renderable : renderLayer.renderables)
		{
			if (!renderable->HasChangedLayer()) continue;
			toFix.push_back(renderable);
		}
	}

	for (Renderable* renderable : toFix)
	{
		remove(renderable);
		add(renderable);
	}
}

void Renderer::ClearCaches()
{
	m_shaderCache.Clear();
	m_bufferCache.Clear();
}

void Renderer::render()
{
	m_window.Clear();

	for (RenderLayer& renderLayer : m_renderLayers)
	{
		//std::cout << renderLayer.layer << ", " << renderLayer.renderables.size() << std::endl;

		for (Renderable* renderable : renderLayer.renderables)
		{
			if (!renderable->IsActive()) continue;
			m_window.Draw(renderable);
		}
	}

	m_window.Display();
}

void Renderer::add(Renderable* renderable)
{
	int layer = renderable->GetLayer();
	renderable->SetLayerUnchanged();

	if (layer > m_renderLayers[m_renderLayers.size() - 1].layer)
	{
		RenderLayer newLayer(layer, renderable);
		m_renderLayers.push_back(newLayer);
		return;
	}

	for (std::vector<RenderLayer>::iterator it = m_renderLayers.begin(); it != m_renderLayers.end(); ++it)
	{
		if (it->layer == layer)
		{
			it->Add(renderable);
			return;
		}

		if (it->layer > layer)
		{
			RenderLayer newLayer(layer, renderable);
			m_renderLayers.insert(it, newLayer);

			return;
		}
	}
}

void Renderer::remove(const Renderable* a_renderable)
{
	for (RenderLayer& renderLayer : m_renderLayers)
	{
		if (renderLayer.layer != a_renderable->GetPrevLayer()) continue;

		for (std::vector<Renderable*>::iterator it = renderLayer.renderables.begin(); it != renderLayer.renderables.end(); ++it)
		{
			if (a_renderable != *it) continue;
			renderLayer.renderables.erase(it);
			return;
		}
	}

	std::cout << "Renderer: Warning: Could NOT remove renderable" << std::endl;
}
