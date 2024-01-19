#include "../../Input/Input.hpp"
#include "../Event/Event.hpp"

class EventHandeler
{
public:
	EventHandeler();

	void HandleEvent(Event& event);
	void ClearButtons();

	//void HandleClicks(Mouse::Button button = Mouse::Button::Left);

private:
	//std::vector<Hoverable*> _hoveringOver;

	//void setHovering(const std::vector<Hoverable*>& hoverables);
};

