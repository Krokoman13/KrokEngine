#include "Engine/KrokEngine.hpp"
#include "Testing/TestScene.hpp"

#include "Testing/UpdateComponent.hpp"
#include "Testing/Button.hpp"
#include <stdlib.h>

int main()
{
	//PathManager::ResetPaths();
	PathManager::MapPaths();

	Game myGame("Demo", 1280, 720, 120);
	myGame.devControls = true;

	myGame.AddScene(new PhysicsScene("Test"));

	{
		Scene* scene = myGame.GetCurrentScene();

		ButtonObject* button = new ButtonObject(RS__BUTTON_PNG, RS__BUTTON_2_PNG, Rectangle(200, 100));
		scene->AddChild(button);
		button->SetLocalPosition(500, 500);
		button->SetFunction([scene]()
			{ 
				GameObject* object = new GameObject("Bullet");
				object->SetLocalPosition(Vec2(100, 100));

				float size = 50.f;
				RigidBody* rb = object->AddComponent<RigidBody>(new CircleCollider(size/2.f));
				rb->velocity = Vec2(100, 0);

				Sprite* sp = object->AddComponent<Sprite>(RS__BALL_PNG);
				sp->SetSize(Vec2(size, size));

				scene->AddChild(object);
			});

		GameObject* laser = new GameObject(Vec2(1000, 100), "Laser");
		TriggerColliderComponent* trigger = laser->AddComponent<TriggerColliderComponent>(std::vector<Vec2>({ Vec2(0, 50), Vec2(0, -50) }));
		Sprite* sprite = laser->AddComponent<Sprite>(RS__PIXEL_PNG);
		sprite->diffuseColor = Color::Red();
		sprite->SetLocalScale(Vec2(2, 100));

		trigger->onTriggerEnterAction = [laser](Collider* a_pCollider)
			{
				TriggerColliderComponent::EnterReport(laser, a_pCollider);
				GameObject* gameObject = a_pCollider->GetColliderComponent()->GetGameObject();
				gameObject->LateDestroy();
			};

		scene->AddChild(laser);
	}

	myGame.Run();
	return 0;
}
