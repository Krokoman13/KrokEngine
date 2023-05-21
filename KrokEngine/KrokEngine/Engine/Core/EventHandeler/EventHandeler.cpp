#include "EventHandeler.hpp"
#include "../UI/Clickable.hpp"
#include "../UI/UI.hpp"
//#include "../../Core/Math/Vec2.hpp"

EventHandeler::EventHandeler(sf::RenderWindow& renderWindow)
{
	_renderWindow = &renderWindow;
}

void EventHandeler::HandleEvent(sf::Event& event, UI* ui)
{
	if (!Input::focus)
	{
		if (event.type == sf::Event::GainedFocus)
		{
			Input::focus = true;
			Input::mouseInScreen = true;
			return;
		}

		return;
	}

	switch (event.type)
	{
	case sf::Event::Closed:
		this->_renderWindow->close();
		break;

	case sf::Event::LostFocus:
		Input::focus = false;
		break;

	case sf::Event::MouseLeft:
		Input::mouseInScreen = false;
		break;
	case sf::Event::MouseEntered:
		Input::mouseInScreen = true;
		break;
	case sf::Event::MouseMoved:
		if (Input::mouseInScreen)
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(*_renderWindow);
			Input::mousePosition.SetXY((float)mousePosition.x, (float)mousePosition.y);
			setHovering(ui->GetHoverables());
		}
		break;
	case sf::Event::MouseButtonPressed:
		if (Input::mouseInScreen)
		{
			Input::mouseButtons[event.mouseButton.button] = true;
			HandleClicks(event.mouseButton.button);
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (Input::mouseInScreen)
		{
			Input::mouseButtons[event.mouseButton.button] = false;
		}
		break;

	case sf::Event::KeyPressed:
		Input::key[event.key.code] = true;
		break;
	case sf::Event::KeyReleased:
		Input::key[event.key.code] = false;
		break;

	default:
		return;
	}
}

void EventHandeler::HandleClicks(sf::Mouse::Button button)
{
	for (size_t i = _hoveringOver.size(); i != 0; i--)
	{
		Clickable* clickable = dynamic_cast<Clickable*>(_hoveringOver[i-1]);

		if (clickable)
		{
			if (clickable->onClickButton == button)
			{
				clickable->OnClick();
				return;
			}
		}
	}
}

bool EventHandeler::ButtonDown(sf::Keyboard::Key pKey)
{
	return Input::key[pKey];
}

void EventHandeler::setHovering(const std::vector<Hoverable*>& hoverables)
{
	while (_hoveringOver.size() > 0)
	{
		Hoverable* oldHoverable = _hoveringOver[_hoveringOver.size() - 1];

		if (oldHoverable != nullptr)
		{
			oldHoverable->hovering = false;
		}

		_hoveringOver.pop_back();
	}

	for (Hoverable* hoverable : hoverables)
	{
		if (hoverable == nullptr) continue;

		if (hoverable->IsInside(Input::mousePosition.x, Input::mousePosition.y))
		{
			hoverable->hovering = true;
			_hoveringOver.push_back(hoverable);
		}
	}
}
