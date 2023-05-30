#include "UpdateManager.hpp"
#include "../../Essentials/ManagedPtr.hpp"
#include "../Math/Vec2.hpp"

UpdateManager::UpdateManager()
{
}

UpdateManager::~UpdateManager()
{
}


void UpdateManager::Update(Scene* scene)
{
	scene->Update();

	for (int i = scene->ChildCount() - 1; i >= 0; --i) {
		ManagedPtr<GameObject> child = scene->GetChild(i);
		update(child);
	}

	for (ManagedPtr<GameObject>  gameObject : scene->ToLoad())
	{
		gameObject->OnLoad();
	}
}

void UpdateManager::SetRenderer(Renderer& renderer)
{
	_renderer = &renderer;
}

void UpdateManager::update(ManagedPtr<GameObject>  toUpdate)
{
	if (toUpdate.IsDestroyed() || !toUpdate->IsActive()) return;

	toUpdate->Update();

	for (int i = toUpdate->ChildCount() - 1; i >= 0; --i) {
		ManagedPtr<GameObject> child = toUpdate->GetChild(i);
		update(child);
	}
}
