#include "UpdateManager.hpp"
#include "../../Essentials/OB_SmartPointers.hpp"
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

	for (unsigned int i = 0; i < scene->ChildCount(); i++)
	{
		update(scene->GetChild(i));
	}

	for (unsigned int i = 0; i < scene->ToLoad().size(); i ++)
	{
		borrow_ptr<GameObject> toLoad = scene->ToLoad()[i];
		toLoad->OnLoad();
	}
}

void UpdateManager::SetRenderer(Renderer& renderer)
{
	_renderer = &renderer;
}

void UpdateManager::update(borrow_ptr<GameObject>  toUpdate)
{
	if (!toUpdate || !toUpdate->IsActive()) return;

	toUpdate->Update();

	for (unsigned int i = 0; i < toUpdate->ChildCount(); i++) 
	{
		update(toUpdate->GetChild(i));
	}

}
