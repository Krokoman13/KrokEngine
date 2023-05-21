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
	toUpdate->Update();

	std::vector<sf::Drawable*> drawables;

	int parentRenderLayer = toUpdate->GetRenderLayer();

	for (int i = toUpdate->ChildCount() - 1; i >= 0; --i) {
		GameObject* gameObject = toUpdate->GetChild(i);
		this->update(gameObject);

		if (gameObject->CanRender())
		{
			sf::Sprite* sprite = gameObject->GetSprite();
			int currentRenderLayer = gameObject->GetRenderLayer();

			if (parentRenderLayer == currentRenderLayer) drawables.push_back(sprite);
			_renderer->ToRender(sprite, currentRenderLayer);
			continue;
		}
	}

	_renderer->ToRender(drawables, parentRenderLayer);
}
