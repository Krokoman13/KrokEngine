#include "UpdateManager.hpp"
#include "../Math/Vec2.hpp"

UpdateManager::UpdateManager()
{
}

UpdateManager::~UpdateManager()
{
}


void UpdateManager::Update(Scene* pScene)
{
	update(pScene);

	for (GameObject* gameObject : pScene->ToLoad())
	{
		gameObject->OnLoad();
	}
}

void UpdateManager::SetRenderer(Renderer& pRenderer)
{
	_renderer = &pRenderer;
}

void UpdateManager::update(GameObject*  pToUpdate)
{
	if (!pToUpdate || !pToUpdate->IsActive()) return;

	pToUpdate->Update();

	if (pToUpdate->CanRender())
	{
		sf::Sprite* sprite = pToUpdate->GetSprite();
		int currentRenderLayer = pToUpdate->GetRenderLayer();
		_renderer->ToRender(sprite, currentRenderLayer);
	}

	for (unsigned int i = 0; i < pToUpdate->ChildCount(); i++) 
	{
		update(pToUpdate->GetChild(i));
	}
}
