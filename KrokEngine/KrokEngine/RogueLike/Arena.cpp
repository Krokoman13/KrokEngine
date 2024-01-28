#include "Arena.hpp"
#include "Barry.hpp"
#include "Chest.hpp"
#include "Monsters/Bat.hpp"
#include "Monsters/Goblin.hpp"
#include "Monsters/Slime.hpp"

void Arena::onLoad()
{
	const float scale = 4.f;
	const float gridSize = 16.f;

	sceneManager->GetGame()->GetCamera().SetScale(scale);

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
}

Vec2 Arena::toGrid(const unsigned int a_x, const unsigned int a_y)
{
	return Vec2(float(a_x), float(a_y)) * m_gridSize + Vec2(m_gridSize, m_gridSize) / 2.f;
}
