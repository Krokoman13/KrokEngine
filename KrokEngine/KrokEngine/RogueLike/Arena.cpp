#include "Arena.hpp"
#include "Barry.hpp"
#include "Chest.hpp"
#include "Monsters/Bat.hpp"
#include "Monsters/Goblin.hpp"
#include "Monsters/Slime.hpp"
#include "../Testing/Button.hpp"

void Arena::onLoad()
{
	_physicsSpeed = 5.f;

	const float scale = 4.f;
	const float gridSize = 16.f;

	SetLocalScale(scale);

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

	m_barry = new Barry(toGrid(10, 5));
	AddChild(m_barry);

	Bat* bat = new Bat(toGrid(20, 0));
	AddChild(bat);
	bat->SetTarget(m_barry);

	Slime* slime = new Slime(toGrid(20, 0));
	AddChild(slime);
	slime->SetTarget(m_barry);

	Goblin* goblin = new Goblin(toGrid(20, 11));
	AddChild(goblin);
	goblin->SetTarget(m_barry);

	Slime* slime2 = new Slime(toGrid(0, 11));
	AddChild(slime2);
	slime2->SetTarget(m_barry);

	m_gameOverScreen = new GameObject("Game Over Screen");
	m_gameOverScreen->AddComponent<Sprite>(RS__COVER_PNG)->SetRenderLayer(1000);
	ButtonObject* button = new ButtonObject(RS__MENU_BUTTON_PNG, RS__MENU_BUTTON_PRESS_PNG, Rectangle(96, 32), 1000);
	button->SetLocalPosition(Vec2(160, 88));
	SceneManager* sceneMng = sceneManager;
	button->SetFunction([sceneMng]() {sceneMng->ReloadCurrentScene(); });
	m_gameOverScreen->AddChild(button);
	AddChild(m_gameOverScreen);
}

void Arena::update()
{
	m_gameOverScreen->SetActive(_physicsSpeed < 0.01f);
}

Vec2 Arena::toGrid(const unsigned int a_x, const unsigned int a_y)
{
	return Vec2(float(a_x), float(a_y)) * float(m_gridSize) + Vec2(float(m_gridSize), float(m_gridSize)) / 2.f;
}
