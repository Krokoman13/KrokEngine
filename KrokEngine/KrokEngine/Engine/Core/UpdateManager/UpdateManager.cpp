#include "UpdateManager.hpp"
#include "../Math/Vec2.hpp"

UpdateManager::UpdateManager()
{
}

UpdateManager::~UpdateManager()
{
}


void UpdateManager::Update(Scene* scene)
{
	update(scene);

	for (unsigned int i = 0; i < scene->ToLoad().size(); i ++)
	{
		GameObject* toLoad = scene->ToLoad()[i];
		toLoad->OnLoad();
	}
}

void UpdateManager::SetRenderer(Renderer& renderer)
{
	_renderer = &renderer;
}

void UpdateManager::update(GameObject*  toUpdate)
{
	if (!toUpdate || !toUpdate->IsActive()) return;

	toUpdate->Update();

	if (toUpdate->CanRender())
	{
		sf::Sprite* sprite = toUpdate->GetSprite();
		int currentRenderLayer = toUpdate->GetRenderLayer();
		_renderer->ToRender(sprite, currentRenderLayer);
	}

	for (unsigned int i = 0; i < toUpdate->ChildCount(); i++) 
	{
		update(toUpdate->GetChild(i));
	}
}
