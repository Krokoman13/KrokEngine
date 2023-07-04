#include <SFML/Graphics.hpp>
#include "../Input/Input.hpp"

//struct Vec2;

class EventHandeler
{
public:
	EventHandeler(sf::RenderWindow& renderWindow);

	void HandleEvent(sf::Event& event);
	void ClearButtons();

	//void HandleClicks(sf::Mouse::Button button = sf::Mouse::Button::Left);

private:
	sf::RenderWindow* _renderWindow;

	//std::vector<Hoverable*> _hoveringOver;

	//void setHovering(const std::vector<Hoverable*>& hoverables);
};

