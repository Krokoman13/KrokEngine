#include "../Input/Input.hpp"

//struct Vec2;

class EventHandeler
{
public:
	EventHandeler(RenderWindow& renderWindow);

	void HandleEvent(Event& event);
	void ClearButtons();

	//void HandleClicks(Mouse::Button button = Mouse::Button::Left);

private:
	RenderWindow* _renderWindow;

	//std::vector<Hoverable*> _hoveringOver;

	//void setHovering(const std::vector<Hoverable*>& hoverables);
};

