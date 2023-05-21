#include <SFML/Graphics.hpp>
#include "../Input/Input.hpp"

class UIElement;
class Hoverable;
class Clickable;
class UI;
//struct Vec2;

class EventHandeler
{
public:
	EventHandeler(sf::RenderWindow& renderWindow);

	void HandleEvent(sf::Event& event, UI* ui);

	void HandleClicks(sf::Mouse::Button button = sf::Mouse::Button::Left);

	bool ButtonDown(sf::Keyboard::Key key);

private:
	sf::RenderWindow* _renderWindow;

	std::vector<Hoverable*> _hoveringOver;

	void setHovering(const std::vector<Hoverable*>& hoverables);
};

