#include "UpdateManager.hpp"
#include "../../Essentials/GmObjctPtr.hpp"
#include "../Math/Vec2.hpp"

UpdateManager::UpdateManager()
{
}

UpdateManager::~UpdateManager()
{
}


void UpdateManager::Update(Scene* scene)
{
	for (GmObjctPtr gameObject : scene->ToLoad())
	{
		gameObject->OnLoad();
	}

	update(scene);
}

void UpdateManager::SetRenderer(Renderer& renderer)
{
	_renderer = &renderer;
}

void UpdateManager::update(GameObject* toUpdate)
{
	if (!toUpdate->IsActive()) return;

	toUpdate->Update();

	if (toUpdate->CanRender())
	{
		sf::Sprite* sprite = toUpdate->GetSprite();
		int currentRenderLayer = toUpdate->GetRenderLayer();
		_renderer->ToRender(sprite, currentRenderLayer);
	}

	for (int i = toUpdate->ChildCount() - 1; i >= 0; --i) {
		GameObject* child = toUpdate->GetChild(i);
		this->update(child);
	}
}
