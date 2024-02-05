#include "Arena.hpp"
#include "Barry.hpp"
#include "Chest.hpp"
#include "Monsters/Bat.hpp"
#include "Monsters/Goblin.hpp"
#include "Monsters/Slime.hpp"

void Arena::onLoad()
{
	_physicsSpeed = 0.f;

	const float scale = 4.f;
	const float gridSize = 16.f;

	//sceneManager->GetGame()->GetCamera().SetScale(scale);
	//SetLocalScale(scale);

	Sprite::defaultMagFilterParam = GL_NEAREST;
	Sprite::defaultMinFilterParam = GL_NEAREST;

	GameObject* backgroundObject = new GameObject(Vec2(-5, -5));
	AddChild(backgroundObject);
	Sprite* backgroundSprite = backgroundObject->AddComponent<Sprite>(RS__LEVELONEBACKGROUND_PNG);
	backgroundSprite->SetDisplayMode(DisplayMode::TopLeft);
	backgroundSprite->SetRenderLayer(-1);

	const float width = 1280.f / scale - 2;
	const float height = 720.f / scale - 5;
	PhysicsObject* box = new PhysicsObject(PolyShape::Rectangle(Vec2(1, 5.f), width, height).Invert(), Vec2(0.f, 0.f));
	box->collider->bounciness = 0.f;
	AddChild(box);

	AddChild(new Chest(toGrid(8, 8)));

	Barry* player = new Barry(toGrid(1, 1));
	AddChild(player);

	Bat* bat = new Bat(toGrid(20, 0));
	AddChild(bat);
	bat->SetTarget(player);

	Goblin* goblin = new Goblin(toGrid(20, 11));
	AddChild(goblin);
	goblin->SetTarget(player);

	Slime* slime = new Slime(toGrid(1, 11));
	AddChild(slime);
	slime->SetTarget(player);

	GameObject* spriteObject = new GameObject();
	circleSprite = spriteObject->AddComponent<Sprite>(RS__BALL_PNG);
	circleSprite->SetDisplayMode(DisplayMode::Center);
	circleSprite->SetRenderLayer(100);
	AddChild(spriteObject);
}

void Arena::update()
{
	circleSprite->SetGlobalPosition(Input::MousePos());

	if (!Input::WentDown(Mouse::Button::Left)) return;

	for (Collider* colliding : OverLayCircle(circleSprite->GetGameObject(),	circleSprite->GetSize().x / 2))
	{
		std::cout << colliding->GetColliderComponent()->GetGameObject()->name << std::endl;
	}

	std::cout << std::endl;
}

Vec2 Arena::toGrid(const unsigned int a_x, const unsigned int a_y)
{
	return Vec2(float(a_x), float(a_y)) * float(m_gridSize) + Vec2(float(m_gridSize), float(m_gridSize)) / 2.f;
}
