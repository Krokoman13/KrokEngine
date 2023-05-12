#include "UpdateManager.hpp"
#include "../../Essentials/GameObject.hpp"
#include "../../Essentials/GmObjctPtr.hpp"
#include "../Graphics/Renderer.hpp"
#include "../Math/Vec2.hpp"


UpdateManager::UpdateManager()
{
}

UpdateManager::~UpdateManager()
{
}


void UpdateManager::Update(GameObject* game)
{
	update(game);
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

	for (int i = toUpdate->GetChildren().size() - 1; i >= 0; --i) {
		GmObjctPtr gameObject = toUpdate->GetChildren()[i];
		this->update(gameObject);

		if (gameObject->canRender)
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
