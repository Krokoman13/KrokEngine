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
	update((GmObjctPtr)scene);

	for (GmObjctPtr gameObject : scene->ToLoad())
	{
		gameObject->OnLoad();
	}
}

void UpdateManager::SetRenderer(Renderer& renderer)
{
	_renderer = &renderer;
}

void UpdateManager::update(GmObjctPtr toUpdate)
{
	if (toUpdate.IsDestroyed() || !toUpdate->IsActive()) return;

	toUpdate->Update();

	for (int i = toUpdate->ChildCount() - 1; i >= 0; --i) {
		GmObjctPtr child = toUpdate->GetChild(i);
		this->update(child);
	}
}
